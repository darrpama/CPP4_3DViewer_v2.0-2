#extension GL_EXT_gpu_shader4 : require
uniform float uPointSize;
uniform int uShapeType; // 0 for square, 1 for circle
uniform vec3 uColor;

layout (location = 0) in vec2 aPosition;

void main()
{
  gl_Position = vec4(aPosition, 0.0, 1.0);
    
  if (uShapeType == 0) { // Square
    gl_PointSize = uPointSize;
  }
  else if (uShapeType == 1) { // Circle
    float radius = uPointSize / 2.0;
    float dist = length(gl_PointCoord - vec2(0.5));
    if (dist > radius) {
      discard;
    }
  }
}