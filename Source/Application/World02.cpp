#include "World02.h"

#include "Framework/Framework.h"

#include "Input/InputSystem.h"

//#define INTERLEAVE
#define INDEX 
namespace nc
{
    ///vertex Buffer world
    bool World02::Initialize()
    {
        ///Shaders!!!
        const char* vertexShader =
            "#version 430\n"//Open Gl Version
            "layout (location=0) in vec3 position;" // Vertex Position
            "layout (location=1) in vec3 color;" 
            "layout (location=0) out vec3 ocolor;" //Pass through/Data passed out
            "void main() {"
            "  ocolor = color;"
            "  gl_Position = vec4(position, 1.0);"
            "}";



        const char* fragmentShader =
            "#version 430\n"
            "layout (location=0) in vec3 color;"
            "out vec4 ocolor;" //Taking in data from vertex shader
            "void main() {"
            "  ocolor = vec4(color, 1);"
            "}";

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs,1,&vertexShader,NULL);
        glCompileShader(vs);


        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragmentShader, NULL);
        glCompileShader(fs);

        GLuint program = glCreateProgram(); // The handle
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glUseProgram(program);

#ifdef INTERLEAVE

        ///vertex Data
       // Define an array of float values representing vertex positions in 3D space.
        float vertexData[] = {
        -0.8f, -0.8f, 0.0f, 1.0f, 1.0f,  1.0f, 
        -0.8f,  0.8f, 0.0f, 1.0f, 1.0f,  0.5f,
         0.8f, -0.8f, 0.0f, 0.8f, 0.5f, -1.0f, 
         0.8f,  0.8f, 0.0f, 1.0f, 1.0f,  1.0f
        };



        // Declare an unsigned integer to store the Vertex Buffer Object (VBO) identifier. // Handle
        GLuint vbo;
        // Generate a VBO and get its identifier.
        glGenBuffers(1, &vbo);
        // Bind the VBO to the GL_ARRAY_BUFFER target.
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // Allocate memory and store the vertex data into the VBO.
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);



        // Generate a VAO and get its identifier.
        glGenVertexArrays(1, &m_vao);
        // Bind the VAO to define what data the shader program will use.
        glBindVertexArray(m_vao);

        glBindVertexBuffer(0, vbo, 0, 6 * sizeof(GLfloat));
        ///Position
        // Enable the first attribute of the vertex shader (usually position).
        glEnableVertexAttribArray(0); // First channel index 0
        // Define how the data for that attribute is retrieved from the VBO.
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(0, 0);

        //Color
        glEnableVertexAttribArray(1); // First channel index 0
        //// Define how the data for that attribute is retrieved from the VBO.
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat));
        glVertexAttribBinding(1, 0);

#elif defined(INDEX)
///vertex Data
     // Define an array of float values representing vertex positions in 3D space.
        const float vertexData[] = {
            -1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top-left
             1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
             1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
            -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f  // bottom-left
        };
        GLuint incdices[] =
        {
            0,1,2,
            2,3,0

        };
        ///vertex buffer object
// Declare an unsigned integer to store the Vertex Buffer Object (VBO) identifier. // Handle
GLuint vbo;
// Generate a VBO and get its identifier.
glGenBuffers(1, &vbo);
// Bind the VBO to the GL_ARRAY_BUFFER target.
glBindBuffer(GL_ARRAY_BUFFER, vbo);
// Allocate memory and store the vertex data into the VBO.
glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    	///Index buffer Object
GLuint ibo;
glGenBuffers(1, &ibo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(incdices),incdices, GL_STATIC_DRAW);

///Vertex Array Object
// Generate a VAO and get its identifier.
glGenVertexArrays(1, &m_vao);
// Bind the VAO to define what data the shader program will use.
glBindVertexArray(m_vao);
glBindVertexBuffer(0, vbo, 0, 6 * sizeof(GLfloat));
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

///Position
// Enable the first attribute of the vertex shader (usually position).
glEnableVertexAttribArray(0); // First channel index 0
// Define how the data for that attribute is retrieved from the VBO.
glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
glVertexAttribBinding(0, 0);

///Color
glEnableVertexAttribArray(1); // First channel index 0
//// Define how the data for that attribute is retrieved from the VBO.
glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
glVertexAttribBinding(1, 0);

#else

        ///vertex Data
        // Define an array of float values representing vertex positions in 3D space.
        float positionData[] = {
		-0.8f, -0.8f, 0.0f,  // Vertex 1: Bottom-left
		-0.8f,  0.8f, 0.0f,  // Vertex 2: Top-left
		 0.8f, -0.8f, 0.0f,  // Vertex 3: Bottom-right
		 0.8f,  0.8f, 0.0f   // Vertex 4: Top-right
        };


        float colorData[] =
        {
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.5f,
            0.8f, 0.5f, -1.0f
        };

        // Declare an unsigned integer to store the Vertex Buffer Object (VBO) identifier.
        GLuint vbo[2];
        // Generate a VBO and get its identifier.
        glGenBuffers(2, vbo);
        // Bind the VBO to the GL_ARRAY_BUFFER target.
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        // Allocate memory and store the vertex data into the VBO.
        glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);


        // array buffer taking in color data
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        // Allocate memory and store the vertex data into the VBO.
        glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

        
        // Generate a VAO and get its identifier.
        glGenVertexArrays(1, &m_vao);
        // Bind the VAO to define what data the shader program will use.
        glBindVertexArray(m_vao);

        ///Position
        // Enable the first attribute of the vertex shader (usually position).
        glEnableVertexAttribArray(0); // First channel index 0
        // Define how the data for that attribute is retrieved from the VBO.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexBuffer(0, vbo[0], 0, 3 * sizeof(GLfloat));

        ///Color
        glEnableVertexAttribArray(1); // First channel index 0
        // Define how the data for that attribute is retrieved from the VBO.
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexBuffer(1, vbo[1], 0, 3 * sizeof(GLfloat));
#endif

        return true;
    }


    void World02::Shutdown()
    {
    }

    void World02::Update(float dt)
    {
        m_angle += 90 * dt;
        //added movement
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_time += dt;
    }

    void World02::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

    	/// render
        glBindVertexArray(m_vao);
#ifdef INDEX
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0); //object drawing, number of vertices, datatype of array, pointer
#else

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // 0 is start and 4 is the amount of vertices drawn
#endif



        // post-render
        renderer.EndFrame();
    }
}
