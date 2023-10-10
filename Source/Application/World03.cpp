#include "World03.h"

#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#define INTERLEAVE

namespace nc
{
	bool World03::Initialize()
	{
		m_program = GET_RESOURCE(Program, "Shaders/unlit_color.prog");
		m_program->Use();

#ifdef INTERLEAVE
		///vertex Data
	   // Define an array of float values representing vertex positions in 3D space.
		float vertexData[] = {
		-0.8f, -0.8f, 0.0f, 1.0f, 1.0f, 1.0f, // Vertex 1: Bottom-left
		-0.8f,  0.8f, 0.0f, 1.0f, 1.0f, 0.5f,// Vertex 2: Top-left
		 0.8f, -0.8f, 0.0f, 0.8f, 0.5f, -1.0f, // Vertex 3: Bottom-right
		 0.8f,  0.8f, 0.0f, 1.0f,1.0f,1.0f// Vertex 4: Top-right
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

	void World03::Shutdown()
	{
	}

	void World03::Update(float dt)
	{

		ENGINE.GetSystem<Gui>()->BeginFrame();
		ImGui::Begin("Transform");
		ImGui::DragFloat3("Position", &m_transform.scale[0]);
		ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
		ImGui::DragFloat3("Scale", &m_transform.scale[0]);
		ImGui::End();
		
		m_transform.rotation.z += 180 * dt;

		//added movement
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * dt : 0;
		m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * dt : 0;
		m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * -dt : 0;
		m_time += dt;

		///model matrix
	//	glm::mat4 position = glm::translate(glm::mat4{ 1 }, m_position); //if the parentheses are confusing, make em brackets
	//	glm::mat4 rotation = glm::rotate(glm::mat4{ 1 }, glm::radians(m_angle), glm::vec3{ 0, 0, 1 });
	//	glm::mat4 model = position * rotation; //make model = position, which was the PREVIOUS mat4 model
		m_program->SetUniform("model", m_transform.GetMatrix());


		///view matrix 
		glm::mat4 view = glm::lookAt(glm::vec3{ 0, 4, 5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }); //make the -5 a 5 or else itll be weird!!!
		m_program->SetUniform("view", view);

		///projection
		glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, 0.01f, 100.0f);
		m_program->SetUniform("projection", projection);
		ENGINE.GetSystem<Gui>()->EndFrame();
		
	}

	void World03::Draw(Renderer& renderer)
	{
		// pre-render
		renderer.BeginFrame();

		/// render
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // 0 is start and 4 is the amount of vertices drawn
		ENGINE.GetSystem<Gui>()->Draw();
		// post-render
		renderer.EndFrame();
	}
}