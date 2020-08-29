#include "ShaderAsset.h"
#include "Texture2D.h"

GLuint VertexArrayID;
//Set material

GLuint indexBuffer;

//Creation of the default shaders, these shaders are named "TextureShader", "ColorShader" and "TextureColorShader"
Shader::Shader()
{
	//init shader

	//shader for textures
	ShaderProgram.emplace("TextureShader", glCreateProgram());

	 pVertexShaderCode = 
		"#version 400 core\n"

		"layout (location = 0) in vec3 Position;\n"
		"layout(location = 1) in vec3 aNormal;\n"
	    "layout(location = 2) in vec2 aTexCoord;\n"

		"uniform mat4 world;\n"
	    "uniform mat4 view;\n"
	    "uniform mat4 projection;\n"

	    "out vec3 Normal;\n"
		"out vec3 FragPos;\n"
	    "out vec2 TexCoord;\n"

		"void main()\n"
		"{\n"
		"gl_Position = projection * view * world * vec4(Position.x, Position.y, Position.z, 1.0);\n"
		 "FragPos = vec3(world * vec4(Position, 1.0));\n"
		"Normal =  mat3(transpose(inverse(world))) * aNormal;\n"
		"TexCoord = aTexCoord;\n"
		"}\0";

	 pFragmentShaderCode =
		"#version 400 core\n"

		"out vec4 FragColor;\n"

		"in vec3 normals;\n"
		"in vec3 FragPos;\n"
		"in vec2 TexCoord;\n"

		"struct Material\n"
		"{\n"
		"sampler2D diffuse;\n"
		"vec3 specular;\n"
		"float shininess;\n"
		"};\n"

		"struct Light\n"
		"{\n"
		"vec3 position;\n"
		"vec3 ambient;\n"
		"vec3 diffuse;\n"
		"vec3 specular;\n"
		"};\n"

		"uniform vec3 viewPos;\n"
		"uniform Material material;\n"
		"uniform Light light\n;"

		"void main()\n"
		"{\n"
		
		//transparency
		"vec4 texture = texture(material.diffuse, TexCoord);\n"
		"if (texture.a < 0.1)\n"
			"discard;\n"

		//ambient
		"vec3 ambient = light.ambient * texture.rgb;\n"

		//diffuse
		"vec3 norm = normalize(normals);\n"
		"vec3 lightDir = normalize(light.position - FragPos);\n"
		"float diff = max(dot(norm, lightDir), 0.0f);\n"
		"vec3 diffuse = light.diffuse * diff * texture.rgb;\n"
		
		//specular
		"vec3 viewDir = normalize(viewPos - FragPos);\n"
		"vec3 reflectDir = reflect(-lightDir, norm);\n"
		"float spec = pow(max(dot(viewDir, reflectDir),0.0f), material.shininess);\n"
		"vec3 specular = light.specular * (spec * material.specular);\n"

		//output
		"vec3 result = ambient + diffuse + specular;\n"
		"FragColor = vec4(result, 1.0f);\n"
	"}\0";

	 SetShader("TextureShader");


	//shader for color only
	ShaderProgram.emplace("ColorShader", glCreateProgram());

	pVertexShaderCode =
		"#version 400 core\n"

		"layout (location = 0) in vec3 Position;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec3 aColor;\n"

		"uniform mat4 world;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"

		"out vec3 Normal;\n"
		"out vec3 FragPos;\n"
		"out vec3 Color;\n"

		"void main()\n"
		"{\n"
		"gl_Position = projection * view * world * vec4(Position.x, Position.y, Position.z, 1.0);\n"
		"FragPos = vec3(world * vec4(Position, 1.0));\n"
		"Normal =  mat3(transpose(inverse(world))) * aNormal;\n"
		"Color = aColor;\n"
		"}\0";

	pFragmentShaderCode =
		"#version 400 core\n"

		"out vec4 FragColor;\n"

		"in vec3 normals;\n"
		"in vec3 FragPos;\n"
		"in vec3 Color;\n"

		"struct Material\n"
		"{\n"
		"vec3 ambient;\n"
		"vec3 diffuse;\n"
		"vec3 specular;\n"
		"float shininess;\n"
		"};\n"

		"struct Light\n"
		"{\n"
		"vec3 position;\n"
		"vec3 ambient;\n"
		"vec3 diffuse;\n"
		"vec3 specular;\n"
		"};\n"

		"uniform vec3 viewPos;\n"
		"uniform Material material;\n"
		"uniform Light light\n;"

		"void main()\n"
		"{\n"

		//ambient
		"vec3 ambient = light.ambient * material.ambient;\n"

		//diffuse
		"vec3 norm = normalize(normals);\n"
		"vec3 lightDir = normalize(light.position - FragPos);\n"
		"float diff = max(dot(norm, lightDir), 0.0f);\n"
		"vec3 diffuse = light.diffuse * diff * material.diffuse;\n"

		//specular
		"vec3 viewDir = normalize(viewPos - FragPos);\n"
		"vec3 reflectDir = reflect(-lightDir, norm);\n"
		"float spec = pow(max(dot(viewDir, reflectDir),0.0f), material.shininess);\n"
		"vec3 specular = light.specular * (spec * material.specular);\n"

		//output
		"vec3 result = ambient + diffuse + specular ;\n"
		"FragColor = vec4(result, 1.0f) * vec4(Color, 1.0f);\n"
		"}\0";

	SetShader("ColorShader");


	//shader for textures & color
	ShaderProgram.emplace("TextureColorShader", glCreateProgram());

	pVertexShaderCode =
		"#version 400 core\n"

		"layout (location = 0) in vec3 Position;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"layout(location = 2) in vec2 aTexCoord;\n"
		"layout(location = 3) in vec3 aColor;\n"

		"uniform mat4 world;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"

		"out vec3 Normal;\n"
		"out vec3 FragPos;\n"
		"out vec2 TexCoord;\n"
		"out vec3 Color;\n"

		"void main()\n"
		"{\n"
		"FragPos = vec3(world * vec4(Position, 1.0));\n"
		"Normal =  mat3(transpose(inverse(world))) * aNormal;\n"
		"TexCoord = aTexCoord;\n"
		"Color = aColor;\n"
		"gl_Position = projection * view * world * vec4(Position.x, Position.y, Position.z, 1.0);\n"
		"}\0";

	pFragmentShaderCode =
		"#version 400 core\n"

		"out vec4 FragColor;\n"

		"in vec3 normals;\n"
		"in vec3 FragPos;\n"
		"in vec2 TexCoord;\n"
		"in vec3 Color;\n"

		"struct Material\n"
		"{\n"
		"sampler2D diffuse;\n"
		"vec3 specular;\n"
		"float shininess;\n"
		"};\n"

		"struct Light\n"
		"{\n"
		"vec3 position;\n"
		"vec3 ambient;\n"
		"vec3 diffuse;\n"
		"vec3 specular;\n"
		"};\n"

		"uniform vec3 viewPos;\n"
		"uniform Material material;\n"
		"uniform Light light\n;"

		"void main()\n"
		"{\n"

		//transparency
		"vec4 texture = texture(material.diffuse, TexCoord) * vec4(Color, 1.0f);\n"
		"if (texture.a < 0.1)\n"
		"discard;\n"

		//ambient
		"vec3 ambient = light.ambient * texture.rgb;\n"

		//diffuse
		"vec3 norm = normalize(normals);\n"
		"vec3 lightDir = normalize(light.position - FragPos);\n"
		"float diff = max(dot(norm, lightDir), 0.0f);\n"
		"vec3 diffuse = light.diffuse * diff * texture.rgb;\n"

		//specular
		"vec3 viewDir = normalize(viewPos - FragPos);\n"
		"vec3 reflectDir = reflect(-lightDir, norm);\n"
		"float spec = pow(max(dot(viewDir, reflectDir),0.0f), material.shininess);\n"
		"vec3 specular = light.specular * (spec * material.specular);\n"

		//output
		"vec3 result = ambient + diffuse + specular;\n"
		"FragColor = vec4(result, 1.0f);\n"
		"}\0";

	SetShader("TextureColorShader");


	ShaderProgram.emplace("TextShader", glCreateProgram());

	pVertexShaderCode =
		"#version 400 core\n"

		"layout(location = 0) in vec4 vertex;\n"
		"out vec2 TexCoord;\n"

		"uniform mat4 projection;\n"

		"void main()\n"
		"{\n"
		"gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
		"TexCoord = vertex.zw;\n"
		"}\0";

	pFragmentShaderCode =
		"#version 400 core\n"

		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"

		"uniform sampler2D text;\n"
		"uniform vec3 textColor;\n"

		"void main()\n"
		"{\n"
		//output
		"vec4 result = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);\n"
		"FragColor = vec4(textColor, 1.0f) * result;\n"
		"}\0";

	SetShader("TextShader");
}

Shader::~Shader()
{
	ShaderProgram.clear();
}

void Shader::AddShader(char* vertexShaderpath, char* fragmentShaderpath, string shaderName)
{
	ShaderProgram.emplace(shaderName, glCreateProgram());
	//code to read shader file

	//end of code to read shader file
	SetShader(shaderName);

	delete[] pVertexShaderCode;
	delete[] pFragmentShaderCode;
}

void Shader::SetShader(string shaderName)
{
	//vertex shader
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* p[1];
	p[0] = pVertexShaderCode;
	GLint Lengths[1];
	Lengths[0] = strlen(pVertexShaderCode);
	glShaderSource(VertexShader, 1, p, Lengths);
	glCompileShader(VertexShader);

	GLint success;
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(VertexShader, sizeof(InfoLog), NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, InfoLog);
	}

	glAttachShader(ShaderProgram.at(shaderName), VertexShader);

	//fragment shader
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* f[1];
	f[0] = pFragmentShaderCode;
	GLint Fragment[1];
	Fragment[0] = strlen(pFragmentShaderCode);
	glShaderSource(FragmentShader, 1, f, Fragment);
	glCompileShader(FragmentShader);


	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(FragmentShader, sizeof(InfoLog), NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_FRAGMENT_SHADER, InfoLog);
	}

	glAttachShader(ShaderProgram.at(shaderName), FragmentShader);

	glLinkProgram(ShaderProgram.at(shaderName));

	GLint Success;
	glGetProgramiv(ShaderProgram.at(shaderName), GL_LINK_STATUS, &Success);
	if (Success == 0) {
		GLchar ErrorLog[1024];
		glGetProgramInfoLog(ShaderProgram.at(shaderName), sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
	}

	glValidateProgram(ShaderProgram.at(shaderName));
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}
	
	

