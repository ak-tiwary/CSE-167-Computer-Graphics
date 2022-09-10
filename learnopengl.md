# **LearnOpenGL.com Tutorial**

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




### **Creating a Window**

We have to create a window, define a context, and handle user input. Some libraries provide this function



</span>


