#ifndef __JS2SCAD__ABSTRACT_OBJECT__HXX
#define __JS2SCAD__ABSTRACT_OBJECT__HXX

#include <ostream>
#include <deque>

namespace js2scad
{

class ObjectsCollection;

class AbstractObject
{
public:
	AbstractObject(ObjectsCollection& collection);
	virtual ~AbstractObject();

	void translate(double dx, double dy, double dz);
	void scale(double dx, double dy, double dz);
	void mirror(double dx, double dy, double dz);
	void resize(double dx, double dy, double dz);
	void rotate(double angle, double x, double y, double z);
	void rotate(double x, double y, double z);

	virtual void toScad(std::ostream& to, size_t indent) const = 0;
protected:
	class AbstractOperation
	{
	public:
		AbstractOperation();
		virtual ~AbstractOperation();

		virtual void toScad(std::ostream& to) const = 0;
	};

	class TranslateOperation : public AbstractOperation
	{
	public:
		TranslateOperation(double dx, double dy, double dz);

		virtual void toScad(std::ostream& to) const;
	private:
		double _dx;
		double _dy;
		double _dz;
	};

	class ScaleOperation : public AbstractOperation
	{
	public:
		ScaleOperation(double dx, double dy, double dz);

		virtual void toScad(std::ostream& to) const;
	private:
		double _dx;
		double _dy;
		double _dz;
	};

	class MirrorOperation : public AbstractOperation
	{
	public:
		MirrorOperation(double dx, double dy, double dz);

		virtual void toScad(std::ostream& to) const;
	private:
		double _dx;
		double _dy;
		double _dz;
	};

	class ResizeOperation : public AbstractOperation
	{
	public:
		ResizeOperation(double dx, double dy, double dz);

		virtual void toScad(std::ostream& to) const;
	private:
		double _dx;
		double _dy;
		double _dz;
	};

	class RotateOperation : public AbstractOperation
	{
	public:
		RotateOperation(double angle, double x, double y, double z);
		RotateOperation(double x, double y, double z);

		virtual void toScad(std::ostream& to) const;
	private:
		bool _hasAngle;
		double _angle;
		double _x;
		double _y;
		double _z;
	};

	void operationsToScad(std::ostream& to) const;

	// TODO: All operations support

	void printIndent(std::ostream& to, size_t indent) const;

private:
	AbstractObject();

	typedef std::deque<AbstractOperation *> OperationsStack;

	ObjectsCollection& _collection;
	OperationsStack _operationsStack;
};

} // namespace js2scad

#endif
