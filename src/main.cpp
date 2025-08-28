#include <iostream> 
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
using namespace std;

void instantiateWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// For Mac
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

int main()
{
	cout << "Let the darkness just take your soul" << endl;

	GLFWwindow* window;
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

	// Render loop
	while(!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	glfwTerminate();
	return 0;
}
