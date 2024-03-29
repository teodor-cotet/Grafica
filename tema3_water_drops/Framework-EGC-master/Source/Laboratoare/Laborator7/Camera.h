#pragma once
#include <iostream>
#include <include/glm.h>
#include <include/math.h>

namespace Mycamera {
	class Camera {

	public:
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;

		Camera() {
			position = glm::vec3(0, 2, 5);
			forward = glm::vec3(0, 0, -1);
			up = glm::vec3(0, 1, 0);
			right = glm::vec3(1, 0, 0);
			
		}

		Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up) {
			Set(position, center, up);
		}

		~Camera() { }

		// Update camera
		void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up) {
			this->position = position;
			forward = glm::normalize(center - position);
			right = glm::cross(forward, up);
			this->up = glm::cross(right, forward);
		}

		void MoveForward(float distance) {
			glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
		}

		void TranslateForward(float distance) {
			position = position + glm::normalize(forward) * distance;
		}

		void TranslateToTarget(float distance) {

			position = position + forward * distance;
		}

		void TranslateUpword(float distance)
		{
			position = position + glm::normalize(up) * distance;
		}

		void TranslateRight(float distance) {

			glm::vec3 projGround = glm::vec3(glm::dot(glm::vec3(1, 0, 0), right), 0, glm::dot(glm::vec3(0, 0, 1), right));
			position = position + glm::normalize(projGround) * distance;
		}

		void RotateFirstPerson_OX(float angle) {

			forward = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1));
			forward = glm::normalize(forward);

			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateFirstPerson_OY(float angle) {

			forward = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1));
			forward = glm::normalize(forward);
			right = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1));
			right = glm::normalize(right);
			up = glm::normalize(glm::cross(right, forward));
		}

		void RotateFirstPerson_OZ(float angle) {

			right = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::vec4(right, 1));
			right = glm::normalize(right);
			up = glm::vec3(glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1)) * glm::vec4(up, 1));
			up = glm::normalize(up);
			forward = glm::normalize(glm::cross(up, right));
		}


		glm::mat4 GetViewMatrix() {

			return glm::lookAt(position, position + forward, up);
		}

	};
}