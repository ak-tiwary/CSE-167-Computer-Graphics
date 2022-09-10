# **CSE 167 Fall 2019 Notes**



## **Lecture 4: Transformations II**

<span style="font-family:'Fira Code'">
 
Homogeneous coordinates allow a unified framework for translation and rotations. No division is performed until the end. 

Scenes can be drawn by pre-and-post-order traversal of the scene graph (see below) where a node is applied, its children are drawn, and then the node is undone if applicable. A stack is required to save state during traversal.

When a transformation $x \to Mx$ is applied to a shape, the normal transforms as $n \to M^{-T}n$ so as to preserve the relation $(M^{-T}n)^T(M t) = 0 $ for any tangent vector at that point.

The formula for rotation about an axis $a$ by an angle $\theta$ is $$R(a,\theta) = \cos\theta I_3 + (1-\cos\theta) aa^T + \sin\theta \widehat{a} $$

### **gluLookAt**

$\verb|gluLookAt|$ defines the camera and is fundamental to viewing images. It has the declaration $$\verb|gluLookAt(eye, center, up)|$$ where each of the three arguments are really triples of $\verb|x,y,z|$ coordinates.

To construct a camera coordinate frame with viewing direction $a$ and up direction of camera $b$ (the "y" direction) we can define $w = \frac{a}{\lvert\lvert a\rvert\rvert}, u = \frac{b \times w} { \lvert\lvert b \times w\rvert\rvert}, $ and $v = w \times u$.

We want to position the camera at the origin and looking down at the $-z$ direction so vector $a$ is the eye direction from the center and vector $b$ is the up direction of the eye.

We first perform the translation and then apply a rotation since we are inverting the usual process that takes the origin and the standard frame to a new frame (we desire that the camera frame be the standard frame centered at origin). This means that the full transformation has matrix $$ M = \begin{bmatrix} R & \mathbf{0} \\ \mathbf{0}^T & 1 \end{bmatrix}\begin{bmatrix} \mathbb{1} & \mathbf{t} \\ \mathbf{0}^{T} & 1\end{bmatrix} = \begin{bmatrix} R & R\mathbf{t} \\ \mathbf{0}^T & 1 \end{bmatrix}$$
The rows of the rotation matrix will be the three unit vectors of the new (camera) coordinate frame since applying this to a  vector produces the dot product with each row and hence the coordinate with respect to that frame. The translation vector $\mathbf{t}$ will be the negative of the location of the camera from the center (or the vector from the camera to the center).



### **Hierarchical Modelling and Scene graphs** (from 6.837 Fa20 Lec 5)
</span>
<span style="font-family:'Fira Code'">
Suppose that we wish to model a robot. We can model the topology of the skeleton as a tree by representing joints as nodes and edges as connections that represent actual connections in the robot. We can then perform a depth first search traversal of the tree and then keep track of the transformation from each node to the head. This allows modularity of design so that each component can be rendered separately and converted directly to global coordinates and yet still has local coordinates.

When we perform the tree traversal we also keep track of state variables (transformation matrices to the root). When we visit a node we compute the transformation from that node to the root by using its parent and then add that to the stack. Since DFS itself uses a stack to determine the order of transversal, we will be able to exactly compute the transformations of future nodes in different branches without ever needing to compute inverses of matrices (which may lead to numerical drift).

A **scene graph** is a generalization of the above where we have several possible node types for shapes, transformations, properties (color, texture), groups etc. These graphs will be directed acyclic graphs (DAGs) since many nodes of certain types can be connected to the shape nodes to represent copies of objects.


</span>


## **Lecture 5: Viewing**

<span style="font-family:'Fira Code'">





</span>
