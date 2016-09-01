// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: system.proto

#ifndef PROTOBUF_system_2eproto__INCLUDED
#define PROTOBUF_system_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_system_2eproto();
void protobuf_AssignDesc_system_2eproto();
void protobuf_ShutdownFile_system_2eproto();

class MsgHeart;
class MsgHeartItem;
class MsgTestBool;

// ===================================================================

class MsgHeartItem : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MsgHeartItem) */ {
 public:
  MsgHeartItem();
  virtual ~MsgHeartItem();

  MsgHeartItem(const MsgHeartItem& from);

  inline MsgHeartItem& operator=(const MsgHeartItem& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MsgHeartItem& default_instance();

  void Swap(MsgHeartItem* other);

  // implements Message ----------------------------------------------

  inline MsgHeartItem* New() const { return New(NULL); }

  MsgHeartItem* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MsgHeartItem& from);
  void MergeFrom(const MsgHeartItem& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MsgHeartItem* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string val = 1;
  void clear_val();
  static const int kValFieldNumber = 1;
  const ::std::string& val() const;
  void set_val(const ::std::string& value);
  void set_val(const char* value);
  void set_val(const char* value, size_t size);
  ::std::string* mutable_val();
  ::std::string* release_val();
  void set_allocated_val(::std::string* val);

  // @@protoc_insertion_point(class_scope:MsgHeartItem)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr val_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_system_2eproto();
  friend void protobuf_AssignDesc_system_2eproto();
  friend void protobuf_ShutdownFile_system_2eproto();

  void InitAsDefaultInstance();
  static MsgHeartItem* default_instance_;
};
// -------------------------------------------------------------------

class MsgHeart : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MsgHeart) */ {
 public:
  MsgHeart();
  virtual ~MsgHeart();

  MsgHeart(const MsgHeart& from);

  inline MsgHeart& operator=(const MsgHeart& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MsgHeart& default_instance();

  void Swap(MsgHeart* other);

  // implements Message ----------------------------------------------

  inline MsgHeart* New() const { return New(NULL); }

  MsgHeart* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MsgHeart& from);
  void MergeFrom(const MsgHeart& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MsgHeart* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 2;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional .MsgHeartItem item = 1;
  bool has_item() const;
  void clear_item();
  static const int kItemFieldNumber = 1;
  const ::MsgHeartItem& item() const;
  ::MsgHeartItem* mutable_item();
  ::MsgHeartItem* release_item();
  void set_allocated_item(::MsgHeartItem* item);

  // optional int32 guid = 3;
  void clear_guid();
  static const int kGuidFieldNumber = 3;
  ::google::protobuf::int32 guid() const;
  void set_guid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MsgHeart)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::MsgHeartItem* item_;
  ::google::protobuf::int32 guid_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_system_2eproto();
  friend void protobuf_AssignDesc_system_2eproto();
  friend void protobuf_ShutdownFile_system_2eproto();

  void InitAsDefaultInstance();
  static MsgHeart* default_instance_;
};
// -------------------------------------------------------------------

class MsgTestBool : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:MsgTestBool) */ {
 public:
  MsgTestBool();
  virtual ~MsgTestBool();

  MsgTestBool(const MsgTestBool& from);

  inline MsgTestBool& operator=(const MsgTestBool& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const MsgTestBool& default_instance();

  void Swap(MsgTestBool* other);

  // implements Message ----------------------------------------------

  inline MsgTestBool* New() const { return New(NULL); }

  MsgTestBool* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const MsgTestBool& from);
  void MergeFrom(const MsgTestBool& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MsgTestBool* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bool test_1 = 1;
  void clear_test_1();
  static const int kTest1FieldNumber = 1;
  bool test_1() const;
  void set_test_1(bool value);

  // optional bool test_2 = 2;
  void clear_test_2();
  static const int kTest2FieldNumber = 2;
  bool test_2() const;
  void set_test_2(bool value);

  // optional bool test_3 = 3;
  void clear_test_3();
  static const int kTest3FieldNumber = 3;
  bool test_3() const;
  void set_test_3(bool value);

  // optional bool test_4 = 4;
  void clear_test_4();
  static const int kTest4FieldNumber = 4;
  bool test_4() const;
  void set_test_4(bool value);

  // optional bool test_5 = 5;
  void clear_test_5();
  static const int kTest5FieldNumber = 5;
  bool test_5() const;
  void set_test_5(bool value);

  // optional bool test_6 = 6;
  void clear_test_6();
  static const int kTest6FieldNumber = 6;
  bool test_6() const;
  void set_test_6(bool value);

  // optional bool test_7 = 7;
  void clear_test_7();
  static const int kTest7FieldNumber = 7;
  bool test_7() const;
  void set_test_7(bool value);

  // optional bool test_8 = 8;
  void clear_test_8();
  static const int kTest8FieldNumber = 8;
  bool test_8() const;
  void set_test_8(bool value);

  // optional bool test_9 = 9;
  void clear_test_9();
  static const int kTest9FieldNumber = 9;
  bool test_9() const;
  void set_test_9(bool value);

  // optional bool test_10 = 10;
  void clear_test_10();
  static const int kTest10FieldNumber = 10;
  bool test_10() const;
  void set_test_10(bool value);

  // optional bool test_11 = 11;
  void clear_test_11();
  static const int kTest11FieldNumber = 11;
  bool test_11() const;
  void set_test_11(bool value);

  // optional bool test_12 = 12;
  void clear_test_12();
  static const int kTest12FieldNumber = 12;
  bool test_12() const;
  void set_test_12(bool value);

  // optional bool test_13 = 13;
  void clear_test_13();
  static const int kTest13FieldNumber = 13;
  bool test_13() const;
  void set_test_13(bool value);

  // optional bool test_14 = 14;
  void clear_test_14();
  static const int kTest14FieldNumber = 14;
  bool test_14() const;
  void set_test_14(bool value);

  // optional bool test_15 = 15;
  void clear_test_15();
  static const int kTest15FieldNumber = 15;
  bool test_15() const;
  void set_test_15(bool value);

  // optional bool test_16 = 16;
  void clear_test_16();
  static const int kTest16FieldNumber = 16;
  bool test_16() const;
  void set_test_16(bool value);

  // optional bool test_17 = 17;
  void clear_test_17();
  static const int kTest17FieldNumber = 17;
  bool test_17() const;
  void set_test_17(bool value);

  // optional bool test_18 = 18;
  void clear_test_18();
  static const int kTest18FieldNumber = 18;
  bool test_18() const;
  void set_test_18(bool value);

  // optional bool test_19 = 19;
  void clear_test_19();
  static const int kTest19FieldNumber = 19;
  bool test_19() const;
  void set_test_19(bool value);

  // optional bool test_20 = 20;
  void clear_test_20();
  static const int kTest20FieldNumber = 20;
  bool test_20() const;
  void set_test_20(bool value);

  // optional bool test_21 = 21;
  void clear_test_21();
  static const int kTest21FieldNumber = 21;
  bool test_21() const;
  void set_test_21(bool value);

  // optional bool test_22 = 22;
  void clear_test_22();
  static const int kTest22FieldNumber = 22;
  bool test_22() const;
  void set_test_22(bool value);

  // optional bool test_23 = 23;
  void clear_test_23();
  static const int kTest23FieldNumber = 23;
  bool test_23() const;
  void set_test_23(bool value);

  // optional bool test_24 = 24;
  void clear_test_24();
  static const int kTest24FieldNumber = 24;
  bool test_24() const;
  void set_test_24(bool value);

  // optional bool test_25 = 25;
  void clear_test_25();
  static const int kTest25FieldNumber = 25;
  bool test_25() const;
  void set_test_25(bool value);

  // optional bool test_26 = 26;
  void clear_test_26();
  static const int kTest26FieldNumber = 26;
  bool test_26() const;
  void set_test_26(bool value);

  // optional bool test_27 = 27;
  void clear_test_27();
  static const int kTest27FieldNumber = 27;
  bool test_27() const;
  void set_test_27(bool value);

  // optional bool test_28 = 28;
  void clear_test_28();
  static const int kTest28FieldNumber = 28;
  bool test_28() const;
  void set_test_28(bool value);

  // optional bool test_29 = 29;
  void clear_test_29();
  static const int kTest29FieldNumber = 29;
  bool test_29() const;
  void set_test_29(bool value);

  // optional bool test_30 = 30;
  void clear_test_30();
  static const int kTest30FieldNumber = 30;
  bool test_30() const;
  void set_test_30(bool value);

  // optional bool test_31 = 31;
  void clear_test_31();
  static const int kTest31FieldNumber = 31;
  bool test_31() const;
  void set_test_31(bool value);

  // optional bool test_32 = 32;
  void clear_test_32();
  static const int kTest32FieldNumber = 32;
  bool test_32() const;
  void set_test_32(bool value);

  // @@protoc_insertion_point(class_scope:MsgTestBool)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  bool test_1_;
  bool test_2_;
  bool test_3_;
  bool test_4_;
  bool test_5_;
  bool test_6_;
  bool test_7_;
  bool test_8_;
  bool test_9_;
  bool test_10_;
  bool test_11_;
  bool test_12_;
  bool test_13_;
  bool test_14_;
  bool test_15_;
  bool test_16_;
  bool test_17_;
  bool test_18_;
  bool test_19_;
  bool test_20_;
  bool test_21_;
  bool test_22_;
  bool test_23_;
  bool test_24_;
  bool test_25_;
  bool test_26_;
  bool test_27_;
  bool test_28_;
  bool test_29_;
  bool test_30_;
  bool test_31_;
  bool test_32_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_system_2eproto();
  friend void protobuf_AssignDesc_system_2eproto();
  friend void protobuf_ShutdownFile_system_2eproto();

  void InitAsDefaultInstance();
  static MsgTestBool* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MsgHeartItem

// optional string val = 1;
inline void MsgHeartItem::clear_val() {
  val_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MsgHeartItem::val() const {
  // @@protoc_insertion_point(field_get:MsgHeartItem.val)
  return val_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MsgHeartItem::set_val(const ::std::string& value) {
  
  val_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MsgHeartItem.val)
}
inline void MsgHeartItem::set_val(const char* value) {
  
  val_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MsgHeartItem.val)
}
inline void MsgHeartItem::set_val(const char* value, size_t size) {
  
  val_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MsgHeartItem.val)
}
inline ::std::string* MsgHeartItem::mutable_val() {
  
  // @@protoc_insertion_point(field_mutable:MsgHeartItem.val)
  return val_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MsgHeartItem::release_val() {
  // @@protoc_insertion_point(field_release:MsgHeartItem.val)
  
  return val_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MsgHeartItem::set_allocated_val(::std::string* val) {
  if (val != NULL) {
    
  } else {
    
  }
  val_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), val);
  // @@protoc_insertion_point(field_set_allocated:MsgHeartItem.val)
}

// -------------------------------------------------------------------

// MsgHeart

// optional string name = 2;
inline void MsgHeart::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MsgHeart::name() const {
  // @@protoc_insertion_point(field_get:MsgHeart.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MsgHeart::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MsgHeart.name)
}
inline void MsgHeart::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MsgHeart.name)
}
inline void MsgHeart::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MsgHeart.name)
}
inline ::std::string* MsgHeart::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:MsgHeart.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MsgHeart::release_name() {
  // @@protoc_insertion_point(field_release:MsgHeart.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MsgHeart::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:MsgHeart.name)
}

// optional .MsgHeartItem item = 1;
inline bool MsgHeart::has_item() const {
  return !_is_default_instance_ && item_ != NULL;
}
inline void MsgHeart::clear_item() {
  if (GetArenaNoVirtual() == NULL && item_ != NULL) delete item_;
  item_ = NULL;
}
inline const ::MsgHeartItem& MsgHeart::item() const {
  // @@protoc_insertion_point(field_get:MsgHeart.item)
  return item_ != NULL ? *item_ : *default_instance_->item_;
}
inline ::MsgHeartItem* MsgHeart::mutable_item() {
  
  if (item_ == NULL) {
    item_ = new ::MsgHeartItem;
  }
  // @@protoc_insertion_point(field_mutable:MsgHeart.item)
  return item_;
}
inline ::MsgHeartItem* MsgHeart::release_item() {
  // @@protoc_insertion_point(field_release:MsgHeart.item)
  
  ::MsgHeartItem* temp = item_;
  item_ = NULL;
  return temp;
}
inline void MsgHeart::set_allocated_item(::MsgHeartItem* item) {
  delete item_;
  item_ = item;
  if (item) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:MsgHeart.item)
}

// optional int32 guid = 3;
inline void MsgHeart::clear_guid() {
  guid_ = 0;
}
inline ::google::protobuf::int32 MsgHeart::guid() const {
  // @@protoc_insertion_point(field_get:MsgHeart.guid)
  return guid_;
}
inline void MsgHeart::set_guid(::google::protobuf::int32 value) {
  
  guid_ = value;
  // @@protoc_insertion_point(field_set:MsgHeart.guid)
}

// -------------------------------------------------------------------

// MsgTestBool

// optional bool test_1 = 1;
inline void MsgTestBool::clear_test_1() {
  test_1_ = false;
}
inline bool MsgTestBool::test_1() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_1)
  return test_1_;
}
inline void MsgTestBool::set_test_1(bool value) {
  
  test_1_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_1)
}

// optional bool test_2 = 2;
inline void MsgTestBool::clear_test_2() {
  test_2_ = false;
}
inline bool MsgTestBool::test_2() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_2)
  return test_2_;
}
inline void MsgTestBool::set_test_2(bool value) {
  
  test_2_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_2)
}

// optional bool test_3 = 3;
inline void MsgTestBool::clear_test_3() {
  test_3_ = false;
}
inline bool MsgTestBool::test_3() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_3)
  return test_3_;
}
inline void MsgTestBool::set_test_3(bool value) {
  
  test_3_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_3)
}

// optional bool test_4 = 4;
inline void MsgTestBool::clear_test_4() {
  test_4_ = false;
}
inline bool MsgTestBool::test_4() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_4)
  return test_4_;
}
inline void MsgTestBool::set_test_4(bool value) {
  
  test_4_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_4)
}

// optional bool test_5 = 5;
inline void MsgTestBool::clear_test_5() {
  test_5_ = false;
}
inline bool MsgTestBool::test_5() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_5)
  return test_5_;
}
inline void MsgTestBool::set_test_5(bool value) {
  
  test_5_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_5)
}

// optional bool test_6 = 6;
inline void MsgTestBool::clear_test_6() {
  test_6_ = false;
}
inline bool MsgTestBool::test_6() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_6)
  return test_6_;
}
inline void MsgTestBool::set_test_6(bool value) {
  
  test_6_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_6)
}

// optional bool test_7 = 7;
inline void MsgTestBool::clear_test_7() {
  test_7_ = false;
}
inline bool MsgTestBool::test_7() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_7)
  return test_7_;
}
inline void MsgTestBool::set_test_7(bool value) {
  
  test_7_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_7)
}

// optional bool test_8 = 8;
inline void MsgTestBool::clear_test_8() {
  test_8_ = false;
}
inline bool MsgTestBool::test_8() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_8)
  return test_8_;
}
inline void MsgTestBool::set_test_8(bool value) {
  
  test_8_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_8)
}

// optional bool test_9 = 9;
inline void MsgTestBool::clear_test_9() {
  test_9_ = false;
}
inline bool MsgTestBool::test_9() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_9)
  return test_9_;
}
inline void MsgTestBool::set_test_9(bool value) {
  
  test_9_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_9)
}

// optional bool test_10 = 10;
inline void MsgTestBool::clear_test_10() {
  test_10_ = false;
}
inline bool MsgTestBool::test_10() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_10)
  return test_10_;
}
inline void MsgTestBool::set_test_10(bool value) {
  
  test_10_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_10)
}

// optional bool test_11 = 11;
inline void MsgTestBool::clear_test_11() {
  test_11_ = false;
}
inline bool MsgTestBool::test_11() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_11)
  return test_11_;
}
inline void MsgTestBool::set_test_11(bool value) {
  
  test_11_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_11)
}

// optional bool test_12 = 12;
inline void MsgTestBool::clear_test_12() {
  test_12_ = false;
}
inline bool MsgTestBool::test_12() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_12)
  return test_12_;
}
inline void MsgTestBool::set_test_12(bool value) {
  
  test_12_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_12)
}

// optional bool test_13 = 13;
inline void MsgTestBool::clear_test_13() {
  test_13_ = false;
}
inline bool MsgTestBool::test_13() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_13)
  return test_13_;
}
inline void MsgTestBool::set_test_13(bool value) {
  
  test_13_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_13)
}

// optional bool test_14 = 14;
inline void MsgTestBool::clear_test_14() {
  test_14_ = false;
}
inline bool MsgTestBool::test_14() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_14)
  return test_14_;
}
inline void MsgTestBool::set_test_14(bool value) {
  
  test_14_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_14)
}

// optional bool test_15 = 15;
inline void MsgTestBool::clear_test_15() {
  test_15_ = false;
}
inline bool MsgTestBool::test_15() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_15)
  return test_15_;
}
inline void MsgTestBool::set_test_15(bool value) {
  
  test_15_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_15)
}

// optional bool test_16 = 16;
inline void MsgTestBool::clear_test_16() {
  test_16_ = false;
}
inline bool MsgTestBool::test_16() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_16)
  return test_16_;
}
inline void MsgTestBool::set_test_16(bool value) {
  
  test_16_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_16)
}

// optional bool test_17 = 17;
inline void MsgTestBool::clear_test_17() {
  test_17_ = false;
}
inline bool MsgTestBool::test_17() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_17)
  return test_17_;
}
inline void MsgTestBool::set_test_17(bool value) {
  
  test_17_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_17)
}

// optional bool test_18 = 18;
inline void MsgTestBool::clear_test_18() {
  test_18_ = false;
}
inline bool MsgTestBool::test_18() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_18)
  return test_18_;
}
inline void MsgTestBool::set_test_18(bool value) {
  
  test_18_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_18)
}

// optional bool test_19 = 19;
inline void MsgTestBool::clear_test_19() {
  test_19_ = false;
}
inline bool MsgTestBool::test_19() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_19)
  return test_19_;
}
inline void MsgTestBool::set_test_19(bool value) {
  
  test_19_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_19)
}

// optional bool test_20 = 20;
inline void MsgTestBool::clear_test_20() {
  test_20_ = false;
}
inline bool MsgTestBool::test_20() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_20)
  return test_20_;
}
inline void MsgTestBool::set_test_20(bool value) {
  
  test_20_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_20)
}

// optional bool test_21 = 21;
inline void MsgTestBool::clear_test_21() {
  test_21_ = false;
}
inline bool MsgTestBool::test_21() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_21)
  return test_21_;
}
inline void MsgTestBool::set_test_21(bool value) {
  
  test_21_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_21)
}

// optional bool test_22 = 22;
inline void MsgTestBool::clear_test_22() {
  test_22_ = false;
}
inline bool MsgTestBool::test_22() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_22)
  return test_22_;
}
inline void MsgTestBool::set_test_22(bool value) {
  
  test_22_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_22)
}

// optional bool test_23 = 23;
inline void MsgTestBool::clear_test_23() {
  test_23_ = false;
}
inline bool MsgTestBool::test_23() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_23)
  return test_23_;
}
inline void MsgTestBool::set_test_23(bool value) {
  
  test_23_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_23)
}

// optional bool test_24 = 24;
inline void MsgTestBool::clear_test_24() {
  test_24_ = false;
}
inline bool MsgTestBool::test_24() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_24)
  return test_24_;
}
inline void MsgTestBool::set_test_24(bool value) {
  
  test_24_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_24)
}

// optional bool test_25 = 25;
inline void MsgTestBool::clear_test_25() {
  test_25_ = false;
}
inline bool MsgTestBool::test_25() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_25)
  return test_25_;
}
inline void MsgTestBool::set_test_25(bool value) {
  
  test_25_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_25)
}

// optional bool test_26 = 26;
inline void MsgTestBool::clear_test_26() {
  test_26_ = false;
}
inline bool MsgTestBool::test_26() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_26)
  return test_26_;
}
inline void MsgTestBool::set_test_26(bool value) {
  
  test_26_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_26)
}

// optional bool test_27 = 27;
inline void MsgTestBool::clear_test_27() {
  test_27_ = false;
}
inline bool MsgTestBool::test_27() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_27)
  return test_27_;
}
inline void MsgTestBool::set_test_27(bool value) {
  
  test_27_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_27)
}

// optional bool test_28 = 28;
inline void MsgTestBool::clear_test_28() {
  test_28_ = false;
}
inline bool MsgTestBool::test_28() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_28)
  return test_28_;
}
inline void MsgTestBool::set_test_28(bool value) {
  
  test_28_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_28)
}

// optional bool test_29 = 29;
inline void MsgTestBool::clear_test_29() {
  test_29_ = false;
}
inline bool MsgTestBool::test_29() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_29)
  return test_29_;
}
inline void MsgTestBool::set_test_29(bool value) {
  
  test_29_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_29)
}

// optional bool test_30 = 30;
inline void MsgTestBool::clear_test_30() {
  test_30_ = false;
}
inline bool MsgTestBool::test_30() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_30)
  return test_30_;
}
inline void MsgTestBool::set_test_30(bool value) {
  
  test_30_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_30)
}

// optional bool test_31 = 31;
inline void MsgTestBool::clear_test_31() {
  test_31_ = false;
}
inline bool MsgTestBool::test_31() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_31)
  return test_31_;
}
inline void MsgTestBool::set_test_31(bool value) {
  
  test_31_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_31)
}

// optional bool test_32 = 32;
inline void MsgTestBool::clear_test_32() {
  test_32_ = false;
}
inline bool MsgTestBool::test_32() const {
  // @@protoc_insertion_point(field_get:MsgTestBool.test_32)
  return test_32_;
}
inline void MsgTestBool::set_test_32(bool value) {
  
  test_32_ = value;
  // @@protoc_insertion_point(field_set:MsgTestBool.test_32)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_system_2eproto__INCLUDED