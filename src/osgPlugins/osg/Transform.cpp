#include "osg/Transform"
#include "osg/MatrixTransform"

#include "osgDB/Registry"
#include "osgDB/Input"
#include "osgDB/Output"

#include "osg/Notify"

using namespace osg;
using namespace osgDB;

// forward declare functions to use later.
bool Transform_readLocalData(Object& obj, Input& fr);
bool Transform_writeLocalData(const Object& obj, Output& fw);

// register the read and write functions with the osgDB::Registry.
RegisterDotOsgWrapperProxy g_TransformProxy
(
    new osg::Transform,
    "Transform",
    "Object Node Transform Group",
    &Transform_readLocalData,
    &Transform_writeLocalData,
    DotOsgWrapper::READ_AND_WRITE
);


bool Transform_readLocalData(Object& obj, Input& fr)
{
    bool iteratorAdvanced = false;

    Transform& transform = static_cast<Transform&>(obj);

    if (fr[0].matchWord("Type"))
    {
        if (fr[1].matchWord("DYNAMIC"))
        {
            transform.setDataVariance(osg::Object::DYNAMIC);
            fr +=2 ;
            iteratorAdvanced = true;
        }
        else if (fr[1].matchWord("STATIC"))
        {
            transform.setDataVariance(osg::Object::STATIC);
            fr +=2 ;
            iteratorAdvanced = true;
        }
        
    }    

    if (fr[0].matchWord("referenceFrame")) {
        if (fr[1].matchWord("RELATIVE_TO_ABSOLUTE") || fr[1].matchWord("ABSOLUTE") ) {
            transform.setReferenceFrame(Transform::ABSOLUTE);
            fr += 2;
            iteratorAdvanced = true;
        }
        if (fr[1].matchWord("RELATIVE_TO_PARENTS") || fr[1].matchWord("RELATIVE")) {
            transform.setReferenceFrame(Transform::RELATIVE);
            fr += 2;
            iteratorAdvanced = true;
        }
    }

    return iteratorAdvanced;
}


bool Transform_writeLocalData(const Object& obj, Output& fw)
{
    const Transform& transform = static_cast<const Transform&>(obj);

    fw.indent() << "referenceFrame ";
    switch (transform.getReferenceFrame()) {
        case Transform::ABSOLUTE:
            fw << "ABSOLUTE\n";
            break;
        case Transform::RELATIVE:
        default:
            fw << "RELATIVE\n";
    };

    return true;
}
