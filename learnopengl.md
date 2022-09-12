# **LearnOpenGL.com Tutorial**

<span style="font-family:'Fira Code'">
These are my notes while following the tutorial. Most of the content here is directly from there without much summarization. These notes are mostly for myself. Please use the original tutorial directly to support the creator. I find that I learn the material better by retyping parts of it like this as I read.

</span>

## **Getting Started**

<span style="font-family:'Fira Code'">

### **OpenGL**

OpenGL is only a specification and developed versions of OpenGL have different implementations according to the same specification. Each graphic card supports specific versions of OpenGL for that card.

Previously OpenGL was used in *immediate mode* (referred to as the *fixed function pipeline*) where most of the functionality was hidden in the library and developers didn't have much control over how OpenGL did its calculations. This was easy to use and understand but it was inefficient. So the specification started to deprecate OpenGL functionality from version 3.2 onwards and motivated programmers to develop in *core-profile mode* and modern practices.

OpenGL is a state machine with a collection of variables that define how OpenGL should currently operate. This state is called the OpenGL *context*. For example, we can change the context from one that draws triangles to one that draws lines. 

An *object* in OpenGL is a collection of options that represents a subset of the state. 

An common workflow in OpenGL is to create an object, store a reference to it as an id, bind the object to the target location of the context, set the options, and then finally un-bind the object by setting the curent object id of the target to 0. Some example (pseudo)code is 

```C++
struct object_name {
    float option1;
    int option2;
    char[] name;
};

struct OpenGL_Context {
    ...
    object_name* object_Window_Target;
    ...
};

//create object
unsigned int objectId = 0;
glGenObject(1, &objectId);
//bind object to context
glBindObject(GL_WINDOW_TARGET, objectId);
//set options of object currently bound
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WIDTH_WIDTH, 800);
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);

//set context target back to default
glBindObject(GL_WINDOW_TARGET, 0);
```




### **Hello Window**

*See code in `hello_window.cpp`. From now on code will be in the appropriate file and notes will be here.*

We wish to instantiate a GLFW window. In the main function we first initialize GLFW with `glfwInit`, after which we configure it using `glfwWindowHint`. The first argument is the option we wish to configure like `GLFW_OPENGL_PROFILE`, `GLFW_CONTEXT_VERSION_MINOR` etc. The second argument is an integer that sets the value of our option. Here setting `CONTEXT_VERSION_MAJOR` and `CONTEXT_VERSION_MINOR` both to 3 tells GLFW that we wish to use OpenGL 3.3 and setting`OPENGL_PROFILE` to `OPENGL_CORE_PROFILE` tells GLFW that we wish to use a smaller subset of core OpeNGL features.

We then create a window with `GLFWwindow* window = glfwCreateWindow(...)` and make the context of our window the main context on the curent thread by `glfwMakeContextCurrent(window)`.

We then tell OpenGL the size of the rendering window using the `glViewport` function. We could set the viewport dimensions to values smaller than GLFW's dimensions and this would mean that all the OpenGL rendering would be displayed in a smaller window. 

When a user resizes the window we would like to adjust the viewport as well. We do this by defining a callback function on the window that gets called each time the function is resized. We can set this by calling `glfwSetFramebufferSizeCallback`. Some other examples of callback functions include processing joystick input changes, error messages etc. We register these functions after we have created the window and before the render loop is initiated.

We then set up a simple *render loop*  that keeps running until we tell GLFW to stop. An iteration of this render loop is called a *frame*. Within the loop we check if any events are triggered by `glfwPollEvents`, in which case we would update the window state and call the corresponding callback methods, and then we swap the color buffer used to render by `glfwSwapBuffers`. This is done because windowing applications use two buffers, one for display and one for drawing, to prevent artifacts that may be created by continuously drawing to directly to the window. These buffers need to be swapped at each time step so that the newly drawn image can be displayed. If we want to clear a buffer we can call `glClear` and specify which buffer (color, depth, or stencil) to clear. Here we choose the `GL_COLOR_BUFFER_BIT` option since we only wish to flush the color values.

To control input we can use some GLFW functions like the `glfwGetKey` function that returns whether a key is currently being pressed. 

### **Hello Triangle**

The graphics pipeline of OpenGL first transforms 3D coordinates to 2D coordinates and then transforms the 2D coordinates to actual color pixels. This pipeline can be divided into several steps that are highly specialized and can be executed in parallel. Modern processing cores run thousands of small programs to process data on the GPU. These small programs are called *shaders*. Some of these shaders are configurable and are written in the *OpenGL Shading Language (GLSL)*. Examples of shaders that can be configured include vertex, geometry and fragment shaders.


Let us describe this pipeline in a bit more detail.

1. As input to the graphics pipeline we pass a collection of 3D vertices (along with color values). 
2. The first step is the *vertex shader* that takes as input a single vertex and transforms the 3D coordinates.
3. The *primitive assembly*stage takes as input all the vertices from the vertex shader and assembles all the points in the primitive shape given (for example, a triangle).
4. The *geometry shader* takes the ouput of the primitive assembly stage and generates other shapes by emitting new vertices to form new primitives.
5. The output of the geometry shader is then passed to the *rasterization stage* where it maps the resulting primitives to the corresponding pixels on the final screen, resulting in fragments for the fragment shader to use. This stage also discards all fragments outside the view for increased performance ("clipping").
6. The *fragment shader* calculates the final color of a pixel using data such as lights, shadows etc.
7. The final stage is the *alpha test* and *blending* stage. This stage checks the corresponding depth value of the fragment to see if it is behind other objects and also checks for `alpha` values (opacity) and blends the object appropriately.

There is also the tesselation stage and transform feedback loop but we will discuss that later.


In most cases we only have to work with the fragment and vertex shaders (there are no default vertex/fragment shaders on the GPU). The geometry shader is optional and is usually left to the default shader.

#### **Vertices and Vertex Shaders**

OpenGL only processes 3D coordinates when they are within $-1.0$ and $1.0$ and these will correspond to visible points on the screen. Such coordinates are called *normalized device coordinates*. The positive $y$-axis points upwards from the center of the graph, the positive $x$-axis points to the right, and the positive $z$ axis is towards the screen. These NDC coordinates will then be transformed to *screen-space coordinates* by the viewport transform using `glViewport`.

Vertex shaders create memory on the GPU to store vertex data, configure how OpenGL should interpret the memory, specify how to send the data to the graphics card, and then process the vertices from memory. This memory is managed via *vertex buffer objects (VBO)* that can store a large number of vertices in the GPU. We try to send as much data as possible at once because sending data to the GPU is relatively slow.

Just like any object in OpenGL, vertex buffers have a unique ID which can be generated using `glGenBuffers`. OpenGL has many types of buffer objects and the buffer type of a vertex buffer object is `GL_ARRAY_BUFFER`. OpenGL allows us to bind to several buffers at once as long as they have a different buffer type. We can bind the newly created buffer to the `GL_ARRAY_BUFFER` target with the `glBindBuffer` function. Doing this ensures that any buffer calls made will be used to configure the currently bound buffer. We can then call `glBufferData` to copy the previously defined vertex data into the buffer's memory. 

The fourth parameter of `glBuffer data specifies how we want the graphics card to manage the given data. This can take 3 forms:

   * `GL_STREAM_DRAW`: the data is set only once and used by the GPU at most a few times.
   * `GL_STATIC_DRAW`: the data is set only once and used many times.
   * `GL_DYNAMIC_DRAW`: the data is changed often and used many times. The graphics card will then place the data in memory that allows for faster rewrites.

We write the vertex shader in the shader language GLSL and then compile this shader so we can use it in our application. Each shader begins with a declaration of its version. In our case we write `#version 330 core` to specify that we are using version 330 (corresponding to OpenGL 3.3) and the core profile functionality.

Now the simplest vertex shader we could write would define a 3-vector variable for input and directly append 1.0 to it to form a 4-vector for output. This is passed to a input variable designated by `in`. We will then pass the desired output value to the predefined `gl_Position`. The final value of `gl_Position` will be used as the output of the vertex shader. In real applications the input data is usually not already in NDC so we have to transform the input data.

To compile a shader we take the source code for the vertex shader and store it in a const C string at the top of the code file. We will then create a vertex shader using `glCreateShader(GL_VERTEX_SHADER)` and pass the source code to this shader object before compiling using `glCompileShader`. We can check if the compilation was successful by getting the compile status using `glGetShaderiv(...,GL_COMPILE_STATUS,..)`.

#### **Fragment Shaders**

 Colors in graphics are represented as RGBA values (where $A$ stands for the opacity $\alpha$) and the strength of each color is a value between $0.0$ and $1.0$. 

 The fragment shader calculates the color output of pixels. It requires only one output 4-vector which we declare using the `out` keyword. We then compile our fragment shader using the `GL_FRAGMENT_SHADER` constant as the shader type.


 #### **Shader Program**

 A shader program object is the final linked version of multiple shaders combined using `glAttachShader` and linked used `glLinkProgram`. If the outputs of a shader do not match with the inputs the next there will be linking errors. We activate the resulting shader program object using `glUseProgram` so that it will be used when we issue render calls. Finally, we delete the shader objects after linking using `glDeleteShader`.

 #### **Linking Vertex Attribute**

 We have to manually specify which part of our input data goes to which vertex attribute in the vertex shader. In our case the vertex buffer data is formatted as $x_1,y_1,z_1,x_2,y_2,z_2,\ldots$ where $(x_k,y_k,z_k)$ is the coordinates of the $k$th vertex. Each number here is a 32 bit (4-bit) floating point value and so we have one attribute of size 3 bytes. We can supply this knowledge to OpenGL using `glVertexAttribPointer` and specifying that the vertex attribute we wish to configure is 0 (the first attribute of each vertex). 

 We then enable the vertex attribute with `glEnableVertexAttribArray` giving the vertex attribute location as its argument. We may now draw the object by using an appropriate OpenGL function.

 #### **Vertex Array Object**

 A vertex array object (VAO) can be bound just like a vertex buffer object and any subsequent vertex attribute calls from that point on will be stored inside the VAO. This has the advantage that when configuring vertex attribute pointers you only have to make those calls once and whenever we want to draw the object, we can just bind the corresponding VAO. This makes switching between different vertex data and attribute configurations easy since we only need to bind a different VAO.

 The VAO stores calls to `glEnableVertexAttribArray`, vertex attribute configurations via `glVertexAttribPointer`, and associated vertex buffer objects. To use a VAO we only have to bind it using `glBindVertexArray`. Whenever we want to draw an object we bind the VAO with the preferred settings and then draw. 

#### **Element Buffer Objects**

If we want to draw a rectangle we would do so by drawing two triangles, but this would lead to an overlap of vertices. We can use element buffer objects (EBOs) to store indices that tells OpenGL which vertices to draw.

This time, we bind the EBO (the generated unsigned integer id) using `GL_ELEMENT_ARRAY_BUFFER` as the buffer type and reuse our VAO to keep track of element buffer object bindings. The last EBO that gets bound while a VAO is bound is stored as the VAO's element buffer object. Binding to a VAO then automatically binds that EBO. We then replace our `glDrawArrays` calls in the render loop with `glDrawElements`.


### **Shaders**

Shaders are small programs that rest on the GPU and are run for each portion of the graphics pipeline. They are written in the OpenGL shading language (GLSL).

#### **GLSL**

Shaders always begin with a version declaration followed by a list of input and output variables, uniforms and its main function.

In the specific case of vertex shaders each input variable is known as a vertex attribute. There is a maximum limit on the number of vertex attributes available. This is always guaranteed to be at least 16.

A vector in GLSL can have 2,3, or 4 dimensions and can be a vector of floats `vecn`, booleans `bvenc`, integers `ivecn`, unsigned integers `uvecn`, and doubles `dvecn`.  Components of a vector can be accessed via $\cdot x, \cdot y, \cdot z, \cdot z$. They may also be accessed using `rgba` for colors or `stpq` for texture coordinates. 

We may define vectors using other vectors in many ways including 
```C++
vec2 someVec;
vec4 otherVec = someVec.xyxx;
vec3 anotherVec = otherVec.zyw;
vec4 diffVec = someVec.xxxx + anotherVec.yxzy;
vec4 result = vec4(somevec, 0.5,0.7);
vec4 answer = vec4(result.xyz, 1.0);
```

In the special case of vertex shaders we have to define how the vertex data is organized by specifying the input variables with location metadata.

To link variables from one shader to the next we should match the types and names on both sides.  

##### **Uniforms**

Uniforms are another way to pass data from our application on the CPU to shaders on the GPU. Uniforms are *global*: a unifrom variable is unique per shader program object and can be accessed from any shader at any stage in the shader program. We can define a uniform in GLSL by using the `uniform` keyword and set it in the OpenGL code rather than in the shader code. To do so we need to find the location of the uniform attribute in our shader using `glGetUniformLocation` and then call `glUniformnf` where $n$ is as appropriate. Note that the latter call should only be made after invoking `glUseProgram`.

##### **More Attributes**

We can add more data to each vertex than just the position. For example, we may wish to add color data which we may pass as another 3 floats representing `RGB` values. We will then have to adjust the vertex shader code and add the line 
```C++
layout (location = 1) in vec3 aColor;
```
to specify the location of this new attribute. We also need to adjust the vertex attribute pointer. For example, the vertex attribute pointer for the new attribute would be defined using the lines
```C++
glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```

### **Textures**

A texture is a 2D image used to add detail to an object. Each vertex in our triangle should have a texture coordinate that specifies which part of the texture image to sample from. Fragment interpolation then does the rest for other fragments.

Texture coordinates range from $(0,0)$ for the lower left corner to $(1,1)$ at the upper right corner. If we ant to specify coordinates outside this ange we have to choose an appropriate behaviour for OpenGL: repeating the image, mirroring and then repeating, clamping the image, etc. These options can be set per coordinate axis $s,t,r$ using the `glTexParameteri`. 

Texture coordinates can be any floating point value but the texture image is discrete (in texels). There are two ways for OpenGL to interpolate the color corresponding to a texture coordinate. The `GL_NEAREST` method selects the texel that is closest to this exact coordinate, while `GL_LINEAR` performs a linear filtering and approximates a color between the texels. 

Texture filtering can also be set for resizing operations. For example, we may use nearest neighbor filtering when textures are scaled downwards and linear filtering when textures are scaled upwards. Both these operations can be set using `glTexParameteri` as below:
```C++
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

To handle arbitrary resizes of objects based on whether they are near or far away, OpenGL uses a concept called *mipmaps*. A mipmap is a collection of texture images where each subsequent texture is twice as small compared to the previous one. OpenGL uses the appropriate texture best suited to the distance to the object.

It is possible to filter between mipmap levels using `NEAREST` and `LINEAR` filtering to prevent artifacts that may arise from switching between mipmap levels. The filtering method can be specified by one of four options:

* `GL_NEAREST_MIPMAP_NEAREST`, which takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling.
* `GL_LINEAR_MIPMAP_LINEAR`, which takes the nearest mipmap level and samples that level using linear interpolation.
* `GL_NEAREST_MIPMAP_LINEAR`, which interpolates between two mipmaps that closely match the size of a pixel and samples the interpolated level via nearest neighbor interpolation.
* `GL_LINEAR_MIPMAP_LINEAR`, which linearly interpolates between the two closest mipmaps and samples the interpolated level via linear interpolation.

A common mistake is to set a mipmap filtering option as the magnification filter. This has no effect since mipmaps are primarily used when the image is downscaled.


#### **Loading and Creating Textures**

We use the `stb_image.h` library to load texture images using `stbi_load`. We then generate and bind textures using IDs just like we would with other objects in OpenGL. Once the texture is bound, we can start use the image data to generate textures:
```C++
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
glGenerateMipmap(GL_TEXTURE_2D);
```
Let us talk about the arguments to the `glTexImage2D` function.

* The first argument specifies the texture target. Since we would have previously bound `GL_TEXTURE_2D` to a texture ID, this operation will generate a texture object at that same target.
* The second argument specifise the mipmap level for which we want to create a texture.
* The third argument tells OpenGL the format to store the texture. 
* The next two arguments sett he width and height of the resulting texture, which we set to the width and height obtained while loading the image.
* The sixth argument should always be 0.
* The seventh and eighth arguments specfiy the format and datatype of the source image. Since we loaded the image with RGB values and store them as chars (1 byte = 8 bits), we pass the corresponding values.
* The last argument is the image data.

One `glTexImage2D` is called, the currently bound texture object now has the texture image attached to it. If we want to use mipmaps we 










</span>
