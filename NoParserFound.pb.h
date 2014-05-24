// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NoParserFound.proto

#ifndef PROTOBUF_NoParserFound_2eproto__INCLUDED
#define PROTOBUF_NoParserFound_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_NoParserFound_2eproto();
void protobuf_AssignDesc_NoParserFound_2eproto();
void protobuf_ShutdownFile_NoParserFound_2eproto();

class NoParserFound;

// ===================================================================

class NoParserFound : public ::google::protobuf::Message {
 public:
  NoParserFound();
  virtual ~NoParserFound();

  NoParserFound(const NoParserFound& from);

  inline NoParserFound& operator=(const NoParserFound& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const NoParserFound& default_instance();

  void Swap(NoParserFound* other);

  // implements Message ----------------------------------------------

  NoParserFound* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NoParserFound& from);
  void MergeFrom(const NoParserFound& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 requestedParserID = 1;
  inline bool has_requestedparserid() const;
  inline void clear_requestedparserid();
  static const int kRequestedParserIDFieldNumber = 1;
  inline ::google::protobuf::uint32 requestedparserid() const;
  inline void set_requestedparserid(::google::protobuf::uint32 value);

  // required uint32 receivedMessageID = 2;
  inline bool has_receivedmessageid() const;
  inline void clear_receivedmessageid();
  static const int kReceivedMessageIDFieldNumber = 2;
  inline ::google::protobuf::uint32 receivedmessageid() const;
  inline void set_receivedmessageid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:NoParserFound)
 private:
  inline void set_has_requestedparserid();
  inline void clear_has_requestedparserid();
  inline void set_has_receivedmessageid();
  inline void clear_has_receivedmessageid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 requestedparserid_;
  ::google::protobuf::uint32 receivedmessageid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_NoParserFound_2eproto();
  friend void protobuf_AssignDesc_NoParserFound_2eproto();
  friend void protobuf_ShutdownFile_NoParserFound_2eproto();

  void InitAsDefaultInstance();
  static NoParserFound* default_instance_;
};
// ===================================================================


// ===================================================================

// NoParserFound

// required uint32 requestedParserID = 1;
inline bool NoParserFound::has_requestedparserid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void NoParserFound::set_has_requestedparserid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void NoParserFound::clear_has_requestedparserid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void NoParserFound::clear_requestedparserid() {
  requestedparserid_ = 0u;
  clear_has_requestedparserid();
}
inline ::google::protobuf::uint32 NoParserFound::requestedparserid() const {
  return requestedparserid_;
}
inline void NoParserFound::set_requestedparserid(::google::protobuf::uint32 value) {
  set_has_requestedparserid();
  requestedparserid_ = value;
}

// required uint32 receivedMessageID = 2;
inline bool NoParserFound::has_receivedmessageid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void NoParserFound::set_has_receivedmessageid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void NoParserFound::clear_has_receivedmessageid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void NoParserFound::clear_receivedmessageid() {
  receivedmessageid_ = 0u;
  clear_has_receivedmessageid();
}
inline ::google::protobuf::uint32 NoParserFound::receivedmessageid() const {
  return receivedmessageid_;
}
inline void NoParserFound::set_receivedmessageid(::google::protobuf::uint32 value) {
  set_has_receivedmessageid();
  receivedmessageid_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_NoParserFound_2eproto__INCLUDED
