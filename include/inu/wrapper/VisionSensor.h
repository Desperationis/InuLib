/** @file VisionSensor.h
 * @brief Wrapper for vision sensor.
 *
 * Wrapper for vision sensor with extra features.
*/ 


#ifndef INUVISIONSENSOR_H
#define INUVISIONSENSOR_H

#include "main.h"
#include "inu/Types.hpp"
#include <memory>


namespace inu {
	class VisionSensor {
	public:
		/**
		 * Note that when this is created, the zero point will default to be at
		 * the topleft.
		 *
		 * @param port Port of the vision sensor [1-20].
		*/ 
		VisionSensor(inu::port port);

		/**
		 * Set the Wi-Fi mode of the Vision Sensor.
		 *
		 * @param enable 0 for disable, 1 for enable.
		*/ 
		void SetWifiMode(const std::uint8_t enable);

		/**
		 * Set a signature to the vision sensor.
		 *
		 * @param signatureID The ID of the signature.
		 * @param signature Pointer to the signature.
		*/ 
		void SetSignature(const std::uint8_t signatureID, pros::vision_signature_s_t* signature);

		/**
		 * Sets the minimum area a detected object must be in order to be
		 * returned by GetLargestObject(). By default, this is set to 200.
		 *
		 * @param minimumArea The minimum area of the object in pixels.
		*/ 
		void SetMinimumArea(unsigned int minimumArea);

		/**
		 * Set the exposure of the vision sensor.
		 *
		 * @param exposure The exposure of the vision sensor between [0, 150].
		*/ 
		void SetExposure(const std::uint8_t exposure);

		/**
		 * Sets the zero point of the vision sensor; The point where all
		 * detected objects are offset from.
		 * 
		 * @param zeroPoint zero point of the vision sensor.
		 */ 
		void SetZeroPoint(pros::vision_zero_e_t zeroPoint);

		/**
		 * Sets a point in the vision sensor such that GetCenterOffset(X or Y)
		 * returns the offset of any object from this point; Useful for when
		 * the front of the robot is offset by an amount.
		 *
		 * @param x The x pixel of the center.
		 *
		 * @param y The y pixel of the center.
		*/ 
		void SetCenterPoint(int x, int y);

		/**
		 * Given a vision object, get its x offset from the center designated
		 * by SetCenterPoint().
		 *
		 * @param object Reference to the detected object.
		 *
		 * @returns In pixels, the X distance between the object and the
		 * center.
		*/ 
		int GetCenterOffsetX(const pros::vision_object_s_t& object) const;

		/**
		 * Given a vision object, get its Y offset from the center designated
		 * by SetCenterPoint().
		 *
		 * @param object Reference to the detected object.
		 *
		 * @returns In pixels, the Y distance between the object and the
		 * center.
		*/ 
		int GetCenterOffsetY(const pros::vision_object_s_t& object) const;

		/**
		 * Get the largest object detected by the vision sensor that has at
		 * least the minimum area set by SetMinimumArea().
		 *
		 * @returns pointer to the object. If no object is detected of minimum
		 * width, return nullptr.
		*/ 
		std::unique_ptr<pros::vision_object_s_t> GetLargestObject() const;

		/**
		 * @returns the number of objects the vision sensor detects; This will
		 * return ALL counted objects regardless of their width.
		*/  
		unsigned int GetObjectCount() const;

		/**
		 * @returns the minimum area a object has to be in order to be returned
		 * by GetLargestObject().
		*/ 
		unsigned int GetMinimumArea() const;

	private:
		pros::Vision vision;
		unsigned int minimumArea;
		int centerX, centerY;
	};
}
#endif
