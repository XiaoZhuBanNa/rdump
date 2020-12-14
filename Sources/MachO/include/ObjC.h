#ifndef ObjC_h
#define ObjC_h

#include <stdio.h>
#include <sstream>

// These are structs in the Objective-C meta data and read to produce the
// comments for disassembly.  While these are part of the ABI they are no
// public defintions.  So the are here not in include/llvm/BinaryFormat/MachO.h
// .

// The cfstring object in a 64-bit Mach-O file.
struct cfstring64_t {
  uint64_t isa;        // class64_t * (64-bit pointer)
  uint64_t flags;      // flag bits
  uint64_t characters; // char * (64-bit pointer)
  uint64_t length;     // number of non-NULL characters in above
};

// The class object in a 64-bit Mach-O file.
struct class64_t {
  uint64_t isa;        // class64_t * (64-bit pointer)
  uint64_t superclass; // class64_t * (64-bit pointer)
  uint64_t cache;      // Cache (64-bit pointer)
  uint64_t vtable;     // IMP * (64-bit pointer)
  uint64_t data;       // class_ro64_t * (64-bit pointer)
};

struct class32_t {
  uint32_t isa;        /* class32_t * (32-bit pointer) */
  uint32_t superclass; /* class32_t * (32-bit pointer) */
  uint32_t cache;      /* Cache (32-bit pointer) */
  uint32_t vtable;     /* IMP * (32-bit pointer) */
  uint32_t data;       /* class_ro32_t * (32-bit pointer) */
};

struct class_ro64_t {
  uint32_t flags;
  uint32_t instanceStart;
  uint32_t instanceSize;
  uint32_t reserved;
  uint64_t ivarLayout;     // const uint8_t * (64-bit pointer)
  uint64_t name;           // const char * (64-bit pointer)
  uint64_t baseMethods;    // const method_list_t * (64-bit pointer)
  uint64_t baseProtocols;  // const protocol_list_t * (64-bit pointer)
  uint64_t ivars;          // const ivar_list_t * (64-bit pointer)
  uint64_t weakIvarLayout; // const uint8_t * (64-bit pointer)
  uint64_t baseProperties; // const struct objc_property_list (64-bit pointer)
};

struct class_ro32_t {
  uint32_t flags;
  uint32_t instanceStart;
  uint32_t instanceSize;
  uint32_t ivarLayout;     /* const uint8_t * (32-bit pointer) */
  uint32_t name;           /* const char * (32-bit pointer) */
  uint32_t baseMethods;    /* const method_list_t * (32-bit pointer) */
  uint32_t baseProtocols;  /* const protocol_list_t * (32-bit pointer) */
  uint32_t ivars;          /* const ivar_list_t * (32-bit pointer) */
  uint32_t weakIvarLayout; /* const uint8_t * (32-bit pointer) */
  uint32_t baseProperties; /* const struct objc_property_list *
                                                   (32-bit pointer) */
};

/* Values for class_ro{64,32}_t->flags */
#define RO_META (1 << 0)
#define RO_ROOT (1 << 1)
#define RO_HAS_CXX_STRUCTORS (1 << 2)

struct method_list64_t {
  uint32_t entsize;
  uint32_t count;
  /* struct method64_t first;  These structures follow inline */
};

struct method_list32_t {
  uint32_t entsize;
  uint32_t count;
  /* struct method32_t first;  These structures follow inline */
};

struct method64_t {
  uint64_t name;  /* SEL (64-bit pointer) */
  uint64_t types; /* const char * (64-bit pointer) */
  uint64_t imp;   /* IMP (64-bit pointer) */
};

struct method32_t {
  uint32_t name;  /* SEL (32-bit pointer) */
  uint32_t types; /* const char * (32-bit pointer) */
  uint32_t imp;   /* IMP (32-bit pointer) */
};

struct protocol_list64_t {
  uint64_t count; /* uintptr_t (a 64-bit value) */
  /* struct protocol64_t * list[0];  These pointers follow inline */
};

struct protocol_list32_t {
  uint32_t count; /* uintptr_t (a 32-bit value) */
  /* struct protocol32_t * list[0];  These pointers follow inline */
};

struct protocol64_t {
  uint64_t isa;                     /* id * (64-bit pointer) */
  uint64_t name;                    /* const char * (64-bit pointer) */
  uint64_t protocols;               /* struct protocol_list64_t *
                                                    (64-bit pointer) */
  uint64_t instanceMethods;         /* method_list_t * (64-bit pointer) */
  uint64_t classMethods;            /* method_list_t * (64-bit pointer) */
  uint64_t optionalInstanceMethods; /* method_list_t * (64-bit pointer) */
  uint64_t optionalClassMethods;    /* method_list_t * (64-bit pointer) */
  uint64_t instanceProperties;      /* struct objc_property_list *
                                                       (64-bit pointer) */
};

struct protocol32_t {
  uint32_t isa;                     /* id * (32-bit pointer) */
  uint32_t name;                    /* const char * (32-bit pointer) */
  uint32_t protocols;               /* struct protocol_list_t *
                                                    (32-bit pointer) */
  uint32_t instanceMethods;         /* method_list_t * (32-bit pointer) */
  uint32_t classMethods;            /* method_list_t * (32-bit pointer) */
  uint32_t optionalInstanceMethods; /* method_list_t * (32-bit pointer) */
  uint32_t optionalClassMethods;    /* method_list_t * (32-bit pointer) */
  uint32_t instanceProperties;      /* struct objc_property_list *
                                                       (32-bit pointer) */
};

struct ivar_list64_t {
  uint32_t entsize;
  uint32_t count;
  /* struct ivar64_t first;  These structures follow inline */
};

struct ivar_list32_t {
  uint32_t entsize;
  uint32_t count;
  /* struct ivar32_t first;  These structures follow inline */
};

struct ivar64_t {
  uint64_t offset; /* uintptr_t * (64-bit pointer) */
  uint64_t name;   /* const char * (64-bit pointer) */
  uint64_t type;   /* const char * (64-bit pointer) */
  uint32_t alignment;
  uint32_t size;
};

struct ivar32_t {
  uint32_t offset; /* uintptr_t * (32-bit pointer) */
  uint32_t name;   /* const char * (32-bit pointer) */
  uint32_t type;   /* const char * (32-bit pointer) */
  uint32_t alignment;
  uint32_t size;
};

struct objc_property_list64 {
  uint32_t entsize;
  uint32_t count;
  /* struct objc_property64 first;  These structures follow inline */
};

struct objc_property_list32 {
  uint32_t entsize;
  uint32_t count;
  /* struct objc_property32 first;  These structures follow inline */
};

struct objc_property64 {
  uint64_t name;       /* const char * (64-bit pointer) */
  uint64_t attributes; /* const char * (64-bit pointer) */
};

struct objc_property32 {
  uint32_t name;       /* const char * (32-bit pointer) */
  uint32_t attributes; /* const char * (32-bit pointer) */
};

struct category64_t {
  uint64_t name;               /* const char * (64-bit pointer) */
  uint64_t cls;                /* struct class_t * (64-bit pointer) */
  uint64_t instanceMethods;    /* struct method_list_t * (64-bit pointer) */
  uint64_t classMethods;       /* struct method_list_t * (64-bit pointer) */
  uint64_t protocols;          /* struct protocol_list_t * (64-bit pointer) */
  uint64_t instanceProperties; /* struct objc_property_list *
                                  (64-bit pointer) */
};

struct category32_t {
  uint32_t name;               /* const char * (32-bit pointer) */
  uint32_t cls;                /* struct class_t * (32-bit pointer) */
  uint32_t instanceMethods;    /* struct method_list_t * (32-bit pointer) */
  uint32_t classMethods;       /* struct method_list_t * (32-bit pointer) */
  uint32_t protocols;          /* struct protocol_list_t * (32-bit pointer) */
  uint32_t instanceProperties; /* struct objc_property_list *
                                  (32-bit pointer) */
};

struct objc_image_info64 {
  uint32_t version;
  uint32_t flags;
};
struct objc_image_info32 {
  uint32_t version;
  uint32_t flags;
};
struct imageInfo_t {
  uint32_t version;
  uint32_t flags;
};
/* masks for objc_image_info.flags */
#define OBJC_IMAGE_IS_REPLACEMENT (1 << 0)
#define OBJC_IMAGE_SUPPORTS_GC (1 << 1)
#define OBJC_IMAGE_IS_SIMULATED (1 << 5)
#define OBJC_IMAGE_HAS_CATEGORY_CLASS_PROPERTIES (1 << 6)

struct message_ref64 {
  uint64_t imp; /* IMP (64-bit pointer) */
  uint64_t sel; /* SEL (64-bit pointer) */
};

struct message_ref32 {
  uint32_t imp; /* IMP (32-bit pointer) */
  uint32_t sel; /* SEL (32-bit pointer) */
};

// Objective-C 1 (32-bit only) meta data structs.

struct objc_module_t {
  uint32_t version;
  uint32_t size;
  uint32_t name;   /* char * (32-bit pointer) */
  uint32_t symtab; /* struct objc_symtab * (32-bit pointer) */
};

struct objc_symtab_t {
  uint32_t sel_ref_cnt;
  uint32_t refs; /* SEL * (32-bit pointer) */
  uint16_t cls_def_cnt;
  uint16_t cat_def_cnt;
  // uint32_t defs[1];        /* void * (32-bit pointer) variable size */
};

struct objc_class_t {
  uint32_t isa;         /* struct objc_class * (32-bit pointer) */
  uint32_t super_class; /* struct objc_class * (32-bit pointer) */
  uint32_t name;        /* const char * (32-bit pointer) */
  int32_t version;
  int32_t info;
  int32_t instance_size;
  uint32_t ivars;       /* struct objc_ivar_list * (32-bit pointer) */
  uint32_t methodLists; /* struct objc_method_list ** (32-bit pointer) */
  uint32_t cache;       /* struct objc_cache * (32-bit pointer) */
  uint32_t protocols;   /* struct objc_protocol_list * (32-bit pointer) */
};

#define CLS_GETINFO(cls, infomask) ((cls)->info & (infomask))
// class is not a metaclass
#define CLS_CLASS 0x1
// class is a metaclass
#define CLS_META 0x2

struct objc_category_t {
  uint32_t category_name;    /* char * (32-bit pointer) */
  uint32_t class_name;       /* char * (32-bit pointer) */
  uint32_t instance_methods; /* struct objc_method_list * (32-bit pointer) */
  uint32_t class_methods;    /* struct objc_method_list * (32-bit pointer) */
  uint32_t protocols;        /* struct objc_protocol_list * (32-bit ptr) */
};

struct objc_ivar_t {
  uint32_t ivar_name; /* char * (32-bit pointer) */
  uint32_t ivar_type; /* char * (32-bit pointer) */
  int32_t ivar_offset;
};

struct objc_ivar_list_t {
  int32_t ivar_count;
  // struct objc_ivar_t ivar_list[1];          /* variable length structure */
};

struct objc_method_list_t {
  uint32_t obsolete; /* struct objc_method_list * (32-bit pointer) */
  int32_t method_count;
  // struct objc_method_t method_list[1];      /* variable length structure */
};

struct objc_method_t {
  uint32_t method_name;  /* SEL, aka struct objc_selector * (32-bit pointer) */
  uint32_t method_types; /* char * (32-bit pointer) */
  uint32_t method_imp;   /* IMP, aka function pointer, (*IMP)(id, SEL, ...)
                            (32-bit pointer) */
};

struct objc_protocol_list_t {
  uint32_t next; /* struct objc_protocol_list * (32-bit pointer) */
  int32_t count;
  // uint32_t list[1];   /* Protocol *, aka struct objc_protocol_t *
  //                        (32-bit pointer) */
};

struct objc_protocol_t {
  uint32_t isa;              /* struct objc_class * (32-bit pointer) */
  uint32_t protocol_name;    /* char * (32-bit pointer) */
  uint32_t protocol_list;    /* struct objc_protocol_list * (32-bit pointer) */
  uint32_t instance_methods; /* struct objc_method_description_list *
                                (32-bit pointer) */
  uint32_t class_methods;    /* struct objc_method_description_list *
                                (32-bit pointer) */
};

struct objc_method_description_list_t {
  int32_t count;
  // struct objc_method_description_t list[1];
};

struct objc_method_description_t {
  uint32_t name;  /* SEL, aka struct objc_selector * (32-bit pointer) */
  uint32_t types; /* char * (32-bit pointer) */
};


#endif
