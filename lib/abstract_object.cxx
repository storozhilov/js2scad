#include "translator_impl.hxx"
#include "abstract_object.hxx"
#include "objects_collection.hxx"
#include <sstream>

namespace js2scad
{

AbstractObject::AbstractObject(ObjectsCollection& collection) :
	_collection(collection),
	_operationsStack()
{
	collection.add(*this);
}

AbstractObject::~AbstractObject()
{
	for (OperationsStack::iterator i = _operationsStack.begin(); i != _operationsStack.end(); ++i) {
		delete (*i);
	}
}

void AbstractObject::translate(double dx, double dy, double dz)
{
	_operationsStack.push_front(new TranslateOperation(dx, dy, dz));
}

void AbstractObject::scale(double dx, double dy, double dz)
{
	_operationsStack.push_front(new ScaleOperation(dx, dy, dz));
}

void AbstractObject::mirror(double dx, double dy, double dz)
{
	_operationsStack.push_front(new MirrorOperation(dx, dy, dz));
}

void AbstractObject::resize(double dx, double dy, double dz)
{
	_operationsStack.push_front(new ResizeOperation(dx, dy, dz));
}

void AbstractObject::rotate(double angle, double x, double y, double z)
{
	_operationsStack.push_front(new RotateOperation(angle, x, y, z));
}

void AbstractObject::rotate(double x, double y, double z)
{
	_operationsStack.push_front(new RotateOperation(x, y, z));
}

void AbstractObject::operationsToScad(std::ostream& to) const
{
	for (OperationsStack::const_iterator i = _operationsStack.begin(); i != _operationsStack.end(); ++i) {
		(*i)->toScad(to);
		to << ' ';
	}
}

void AbstractObject::printIndent(std::ostream& to, size_t indent) const
{
	for (size_t i = 0; i < indent * _collection.getTranslator().getIndentWidth(); ++i) {
		to << ' ';
	}
}

//------------------------------------------------------------------------------

AbstractObject::AbstractOperation::AbstractOperation()
{}

AbstractObject::AbstractOperation::~AbstractOperation()
{}

//------------------------------------------------------------------------------

AbstractObject::TranslateOperation::TranslateOperation(double dx, double dy, double dz) :
	_dx(dx),
	_dy(dy),
	_dz(dz)
{}

void AbstractObject::TranslateOperation::toScad(std::ostream& to) const
{
	to << "translate([" << _dx << ", " << _dy << ", " << _dz << "])";
}

//------------------------------------------------------------------------------

AbstractObject::ScaleOperation::ScaleOperation(double dx, double dy, double dz) :
	_dx(dx),
	_dy(dy),
	_dz(dz)
{}

void AbstractObject::ScaleOperation::toScad(std::ostream& to) const
{
	to << "scale([" << _dx << ", " << _dy << ", " << _dz << "])";
}

//------------------------------------------------------------------------------

AbstractObject::MirrorOperation::MirrorOperation(double dx, double dy, double dz) :
	_dx(dx),
	_dy(dy),
	_dz(dz)
{}

void AbstractObject::MirrorOperation::toScad(std::ostream& to) const
{
	to << "mirror([" << _dx << ", " << _dy << ", " << _dz << "])";
}

//------------------------------------------------------------------------------

AbstractObject::ResizeOperation::ResizeOperation(double dx, double dy, double dz) :
	_dx(dx),
	_dy(dy),
	_dz(dz)
{}

void AbstractObject::ResizeOperation::toScad(std::ostream& to) const
{
	to << "resize([" << _dx << ", " << _dy << ", " << _dz << "])";
}

//------------------------------------------------------------------------------

AbstractObject::RotateOperation::RotateOperation(double angle, double x, double y, double z) :
	_hasAngle(true),
	_angle(angle),
	_x(x),
	_y(y),
	_z(z)
{}

AbstractObject::RotateOperation::RotateOperation(double x, double y, double z) :
	_hasAngle(false),
	_angle(),
	_x(x),
	_y(y),
	_z(z)
{}

void AbstractObject::RotateOperation::toScad(std::ostream& to) const
{
	if (_hasAngle) {
		to << "rotate(a = " << _angle << ", v = [" << _x << ", " << _y << ", " << _z << "])";
	} else {
		to << "rotate(a = [" << _x << ", " << _y << ", " << _z << "])";
	}
}

//------------------------------------------------------------------------------

} // namespace js2scad
