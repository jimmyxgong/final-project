#pragma once

#include "Commons.h"
#include "Quaternion.h"
#include "Entity.h"

#include <list>

#define IDENTITY Matrix4f()

// Forward declaration for bypassing cross referencing
class GameObject;

class Transform {
private:
	/* Orientation relative to a parent's world matrix */
	Vector3f    localScale;
	Vector3f	localPosition;
	Quaternion  localRotation;

	/* Orientation in world matrix */
	Vector3f	scaling;
	Vector3f	position;
	Quaternion	rotation;

	/* Point in each respective space to another space*/
	Matrix4f	localToWorldMatrix;
	Matrix4f	worldToLocalMatrix;

	/* Children used in Scene Graph */
	std::list<SharedPointer<Transform>> children;
	Transform * parent;

	// Needs to be shared so that gameObject does not get
	// deleted if it is just a locally bound variable
	SharedPointer<GameObject> gameObject;

public:	/* Getters and Setters */

	Matrix4f    worldMatrix;

	Vector3f getLocalScale() const;
	Vector3f getLocalPosition() const;
	Quaternion getLocalRotation() const;

	Vector3f getPosition() const;
	Quaternion getRotation() const;

	Matrix4f getLocalToWorldMatrix() const;

	Transform& setLocalScale(const Vector3f & val);
	Transform& setLocalPosition(const Vector3f & val);
	Transform& setLocalRotation(const Quaternion & val);

	Transform& setPosition(const Vector3f & val);
	Transform& setRotation(const Quaternion & val);

public: /* Transformations on current orientation */

	Transform& scaleLocal(float xyz);
	Transform& scaleLocal(float x, float y, float z);
	Transform& scaleLocal(const Vector3f & val);

	Transform& rotateLocalX(float deg);
	Transform& rotateLocalY(float deg);
	Transform& rotateLocalZ(float deg);
	Transform& rotateLocal(float x, float y, float z, float deg);
	Transform& rotateLocal(Quaternion & val);

	Transform& translateLocal(float x, float y, float z);
	Transform& translateLocal(const Vector3f & val);


public: /* Constructors */
	/* Copy Constructor */
	Transform(const Transform &);	
	Transform();
	~Transform();

public: /* Scene Graph */

	// Get's the parent's localToWorldMatrix and update recursively
	// itself and all of its children just like a regular scene graph
	// node would.
	Transform& locallyUpdate(const Matrix4f & val = IDENTITY);

	Transform& resetScale();
	Transform& resetPosition();
	Transform& resetRotation();

	// Reset orientation to base orientation
	Transform& reset();

	// Add a child to the Transform's children.
	Transform& addChild(SharedPointer<Transform> const & transform);

	Transform& addChild(SharedPointer<GameObject> const & transform);

	// Render itself if has an attached gameObject, and its children
	void renderAll();
	void updateAll();

public:
	bool changed;
	bool hasChanged();












	void rotate(float x, float y, float z);
	void rotate(Quaternion& quat);
	void rotate(Vector3f& vec);

	void translate(float x, float y, float z);
	void translate(Vector3f& vec);

	void scale(float x);
	






	void updateWorldMatrix();
	void updateLocalWorldMatrix();
	Matrix4f asMatrix();



public:





	void destroy();





	// Create a scalable matrix
	static Matrix4f ScaleMatrix(float);
	
	// Rotate input matrix about the pitch axis
	static Matrix4f RotateX(Matrix4f&, float);

	// Rotate input matrix about the yaw axis
	static Matrix4f RotateY(Matrix4f&, float);

	// Rotate input matrix about the roll axis
	static Matrix4f RotateZ(Matrix4f&, float);

	// Translate a given matrix by x, y, z
	static Matrix4f Translate(Matrix4f&, float x, float y, float z);


	const static Matrix4f Translate(float x, float y, float z);
	const static Matrix4f Translate(Vector3f&);

	const static Matrix4f Scale(float x, float y, float z);
	const static Matrix4f Scale(Vector3f&);

	const static Matrix4f StripTranslation(Matrix4f const &);
	const static Matrix4f StripTranslation(Matrix4f const &, float val);
};