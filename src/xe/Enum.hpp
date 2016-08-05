
#ifndef __xe_enum_hpp__
#define __xe_enum_hpp__

#define XE_ENUM_BEGIN(EnumName) \
    struct EnumName {           \
        enum Enum {                                 

#define XE_ENUM_FIELD(FieldName)    \
            FieldName,

#define XE_ENUM_FIELD_VALUE(FieldName, FieldValue)  \
            FieldName = FieldValue,

#define XE_ENUM_END(EnumName)                       \
        };                                          \
        EnumName() {}                               \
        EnumName(Enum value) : m_value(value) {}    \
        operator Enum() const {return m_value;}     \
        Enum m_value;                               \
    };

//namespace xe {
//
//    template<typename Type> 
//    struct Enumeration {
//        typedef typename Type::Enum EnumType;
//
//        Enumeration() {}
//
//        Enumeration(const EnumType value) : m_value(value) {}
//
//        operator EnumType() const {
//            return m_value;
//        }
//
//        operator int() const {
//            return m_value;
//        }
//
//    protected:
//        EnumType m_value;
//    };
//}

#endif 
