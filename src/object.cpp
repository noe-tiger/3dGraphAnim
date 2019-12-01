#include <iostream>
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "controls.hpp"
#include "object.hpp"

namespace Tetris {
  Cubi::Cubi(GLuint &matrixID,
	     GLuint &modelMatrixID,
	     GLuint &viewMatrixID,
	     GLuint &lightID,
	     GLuint &textureID,
	     size_t objSize,
	     GLuint &vertexbuffer,
	     GLuint &uvbuffer,
	     GLuint &normalbuffer,
	     Tetris::Texture &texture) :
    _matrixID(matrixID),
    _modelMatrixID(modelMatrixID),
    _viewMatrixID(viewMatrixID),
    _lightID(lightID),
    _textureID(textureID),
    _objSize(objSize),
    _vertexbuffer(vertexbuffer),
    _uvbuffer(uvbuffer),
    _normalbuffer(normalbuffer),
    _texture(texture)
  {
  }

  Cubi::~Cubi() {
    glDeleteBuffers(1, &this->_vertexbuffer);
    glDeleteBuffers(1, &this->_uvbuffer);
    glDeleteBuffers(1, &this->_normalbuffer);
  }
  
  void Cubi::setupPosition(glm::vec3 &orientation,
			   glm::vec3 &position,
			   glm::vec3 &scale,
			   glm::vec3 &lightPos) {
    this->_orientation = orientation;
    this->_position = position;
    this->_scale = scale;
    this->_lightPos = lightPos;
  }

  void Cubi::draw() {
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 RotationMatrix = glm::eulerAngleYXZ(this->_orientation.y, this->_orientation.x, this->_orientation.z);
    glm::mat4 TranslationMatrix = glm::translate(RotationMatrix, this->_position);
    glm::mat4 ModelMatrix = glm::scale(TranslationMatrix, this->_scale);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    
    glUniformMatrix4fv(this->_matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(this->_modelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(this->_viewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    glUniform3f(this->_lightID, this->_lightPos.x, this->_lightPos.y, this->_lightPos.z);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_texture.getTexture());
    glUniform1i(this->_textureID, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->_normalbuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, this->_objSize );
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

}
