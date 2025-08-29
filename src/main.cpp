#include <iostream> 
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
using namespace std;


// I love globals
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// knock knock, who's there. banana. banana who? orange. 
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


void instantiateWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// For Mac
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

void processKeyboardInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

bool createWindowObject(GLFWwindow*& window)
{
	window = glfwCreateWindow(800, 600, "LearnOpenGLv2", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window." << endl;
		cout << "time to cry in the shower while listening to korn" << endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

bool initializeGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD, so now we are SAD" << endl;
		return false;
	}
	return true;
}

void setViewportSize()
{
	glViewport(0, 0, 800, 600);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void handleViewportAdjustments(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  
}

void useVertexArray(unsigned int& VAO, unsigned int& VBO, float vertices[], int sizeOfVertices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);
}

void setVertexAttributesPointers()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  
}

void unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

unsigned int createVertexShader()
{
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	return vertexShader;
}

void attachAndCompileVertexShader(unsigned int vertexShader)
{
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
}

void checkForSuccessfulShaderCompile(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "Error: Shader compilation failed :( " << infoLog << endl;
	}
}

void checkForSuccessfulProgramLink(unsigned int shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "Error! Shader program linking failed :( " << endl; 
	}
}

unsigned int createFragmentShader()
{
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	return fragmentShader;
}

void attachAndCompileFragmentShader(unsigned int fragmentShader)
{
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
}

unsigned int createShaderProgram()
{
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	return shaderProgram;
}

void linkShaders(unsigned int shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
}

void cleanUp(unsigned int vertexShader, unsigned int fragmentShader)
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void deallocateResources(unsigned int VAO, unsigned int VBO, unsigned int shaderProgram)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void renderBackground()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawTriangle(unsigned int VAO, unsigned int shaderProgram)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
	cout << "Let the darkness just take your soul" << endl;

	GLFWwindow* window;
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};  
	instantiateWindow();
	bool createWindowSuccess = createWindowObject(window);
	if (!createWindowSuccess)
	{
		return -1;
	}

	int gladSuccess = initializeGlad();
	if (!gladSuccess)
	{
		return -1;
	}

	setViewportSize();
	handleViewportAdjustments(window);

	// Vertex shader computations and checks, aw yiss
	unsigned int vertexShader = createVertexShader();
	attachAndCompileVertexShader(vertexShader);
	checkForSuccessfulShaderCompile(vertexShader);

	// Fragment shader computations, hell yeah
	unsigned int fragmentShader = createFragmentShader();
	attachAndCompileFragmentShader(fragmentShader);
	checkForSuccessfulShaderCompile(fragmentShader);

	// Linking
	unsigned int shaderProgram = createShaderProgram();
	linkShaders(shaderProgram, vertexShader, fragmentShader);
	checkForSuccessfulProgramLink(shaderProgram);

	cleanUp(vertexShader, fragmentShader);

	// VAOs/VBOs
	unsigned int VAO, VBO;
	useVertexArray(VAO, VBO, vertices, sizeof(vertices));
	setVertexAttributesPointers();
	unbind();

	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		processKeyboardInput(window);
		// Make light grayish-green color appear:
		renderBackground();
		drawTriangle(VAO, shaderProgram);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	deallocateResources(VAO, VBO, shaderProgram);

	glfwTerminate();
	return 0;
}
