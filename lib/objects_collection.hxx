#ifndef __JS2SCAD__OBJECTS_COLLECTION__HXX
#define __JS2SCAD__OBJECTS_COLLECTION__HXX

#include "abstract_object.hxx"
#include <vector>
#include <map>
#include <ostream>

namespace js2scad
{

class TranslatorImpl;

class ObjectsCollection
{
public:
	ObjectsCollection(TranslatorImpl& translator);
	~ObjectsCollection();

	inline TranslatorImpl& getTranslator() const
	{
		return _translator;
	}

	size_t add(AbstractObject& obj);
	void reset();
	void toScad(std::ostream& to) const;
private:
	ObjectsCollection();

	typedef std::vector<AbstractObject *> ObjectsContainer;
	typedef std::map<AbstractObject *, size_t> RootObjects;

	void setNonRoot(AbstractObject& item);

	TranslatorImpl& _translator;
	ObjectsContainer _objectsContainer;
	RootObjects _rootObjects;

	friend class AbstractCollectionObject;
};

} // namespace js2scad

#endif
