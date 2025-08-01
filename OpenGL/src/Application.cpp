#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    // initiate the core profile, make sure to have a vao setup for this to work
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "ZacStack.dev", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLCall(glfwSwapInterval(1));

    if (glewInit() != GLEW_OK)
        std::cout << "Error!\n";

    std::cout << glGetString(GL_VERSION) << "\n";
    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,   //0
             0.5f, -0.5f, 1.0f, 0.0f,   //1
             0.5f,  0.5f, 1.0f, 1.0f,   //2
            -0.5f,  0.5f, 0.0f, 1.0f    //3
        };

        unsigned int indicies[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        

        // creates vao for core profile
        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));
        

        // vertex array init
        VertexArray va;
        // creates vertex buffer
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        // make vertex buffer layout
        VertexBufferLayout layout;
        layout.Push<float>(2); // positions
        layout.Push<float>(2); // texcoord
        va.AddBuffer(vb, layout);

        // creates index buffer
        IndexBuffer ib(indicies, 6);

        glm::mat4 proj = glm::ortho(-2.f, 2.f, -1.5f, 1.5f, -1.f, 1.f);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/lion.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0); // 0 in this case should match the slot that the texture is bound to 

        // clear everything
        va.Unbind();
        vb.Unbind();
        ib.Unbind(); 
        shader.Unbind();

        Renderer renderer;

        // set r variable for red color
        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();


            //shader.Bind();
            shader.Bind();
            texture.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}