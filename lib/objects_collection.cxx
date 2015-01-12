#include "objects_collection.hxx"
#include "translator_impl.hxx"

namespace js2scad
{

ObjectsCollection::ObjectsCollection(TranslatorImpl& translator) :
	_translator(translator),
	_objectsContainer(),
	_rootObjects()
{}

ObjectsCollection::~ObjectsCollection()
{
	reset();
}

size_t ObjectsCollection::add(AbstractObject& obj)
{
	_objectsContainer.push_back(&obj);
	_rootObjects.insert(RootObjects::value_type(&obj, _objectsContainer.size() - 1));
	return _objectsContainer.size() - 1;
}

void ObjectsCollection::reset()
{
	_rootObjects.clear();
	for (size_t i = 0U; i < _objectsContainer.size(); ++i) {
		delete _objectsContainer[i];
	}
	_objectsContainer.clear();
}

void ObjectsCollection::setNonRoot(AbstractObject& item)
{
	_rootObjects.erase(&item);
}

void ObjectsCollection::toScad(std::ostream& to) const
{
	bool isFirstLine = true;
	for (size_t i = 0U; i < _objectsContainer.size(); ++i) {
		if (_rootObjects.find(_objectsContainer[i]) == _rootObjects.end()) {
			continue;
		}
		if (isFirstLine) {
			isFirstLine = false;
		} else {
			to << std::endl;
		}
		_objectsContainer[i]->toScad(to, 0);
	}
}

} // namespace js2scad
