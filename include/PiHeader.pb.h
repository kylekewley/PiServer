// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PiHeader.proto

#ifndef PROTOBUF_PiHeader_2eproto__INCLUDED
#define PROTOBUF_PiHeader_2eproto__INCLUDED

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
void  protobuf_AddDesc_PiHeader_2eproto();
void protobuf_AssignDesc_PiHeader_2eproto();
void protobuf_ShutdownFile_PiHeader_2eproto();

class PiHeader;

// ===================================================================

class PiHeader : public ::google::protobuf::Message {
 public:
  PiHeader();
  virtual ~PiHeader();

  PiHeader(const PiHeader& from);

  inline PiHeader& operator=(const PiHeader& from) {
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
  static const PiHeader& default_instance();

  void Swap(PiHeader* other);

  // implements Message ----------------------------------------------

  PiHeader* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PiHeader& from);
  void MergeFrom(const PiHeader& from);
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

  // required uint32 messageLength = 1;
  inline bool has_messagelength() const;
  inline void clear_messagelength();
  static const int kMessageLengthFieldNumber = 1;
  inline ::google::protobuf::uint32 messagelength() const;
  inline void set_messagelength(::google::protobuf::uint32 value);

  // required uint32 parserID = 2;
  inline bool has_parserid() const;
  inline void clear_parserid();
  static const int kParserIDFieldNumber = 2;
  inline ::google::protobuf::uint32 parserid() const;
  inline void set_parserid(::google::protobuf::uint32 value);

  // optional uint32 messageID = 3;
  inline bool has_messageid() const;
  inline void clear_messageid();
  static const int kMessageIDFieldNumber = 3;
  inline ::google::protobuf::uint32 messageid() const;
  inline void set_messageid(::google::protobuf::uint32 value);

  // optional uint32 flags = 4;
  inline bool has_flags() const;
  inline void clear_flags();
  static const int kFlagsFieldNumber = 4;
  inline ::google::protobuf::uint32 flags() const;
  inline void set_flags(::google::protobuf::uint32 value);

  // optional bool successResponse = 5;
  inline bool has_successresponse() const;
  inline void clear_successresponse();
  static const int kSuccessResponseFieldNumber = 5;
  inline bool successresponse() const;
  inline void set_successresponse(bool value);

  // @@protoc_insertion_point(class_scope:PiHeader)
 private:
  inline void set_has_messagelength();
  inline void clear_has_messagelength();
  inline void set_has_parserid();
  inline void clear_has_parserid();
  inline void set_has_messageid();
  inline void clear_has_messageid();
  inline void set_has_flags();
  inline void clear_has_flags();
  inline void set_has_successresponse();
  inline void clear_has_successresponse();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 messagelength_;
  ::google::protobuf::uint32 parserid_;
  ::google::protobuf::uint32 messageid_;
  ::google::protobuf::uint32 flags_;
  bool successresponse_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_PiHeader_2eproto();
  friend void protobuf_AssignDesc_PiHeader_2eproto();
  friend void protobuf_ShutdownFile_PiHeader_2eproto();

  void InitAsDefaultInstance();
  static PiHeader* default_instance_;
};
// ===================================================================


// ===================================================================

// PiHeader

// required uint32 messageLength = 1;
inline bool PiHeader::has_messagelength() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PiHeader::set_has_messagelength() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PiHeader::clear_has_messagelength() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PiHeader::clear_messagelength() {
  messagelength_ = 0u;
  clear_has_messagelength();
}
inline ::google::protobuf::uint32 PiHeader::messagelength() const {
  return messagelength_;
}
inline void PiHeader::set_messagelength(::google::protobuf::uint32 value) {
  set_has_messagelength();
  messagelength_ = value;
}

// required uint32 parserID = 2;
inline bool PiHeader::has_parserid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PiHeader::set_has_parserid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PiHeader::clear_has_parserid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PiHeader::clear_parserid() {
  parserid_ = 0u;
  clear_has_parserid();
}
inline ::google::protobuf::uint32 PiHeader::parserid() const {
  return parserid_;
}
inline void PiHeader::set_parserid(::google::protobuf::uint32 value) {
  set_has_parserid();
  parserid_ = value;
}

// optional uint32 messageID = 3;
inline bool PiHeader::has_messageid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PiHeader::set_has_messageid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PiHeader::clear_has_messageid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PiHeader::clear_messageid() {
  messageid_ = 0u;
  clear_has_messageid();
}
inline ::google::protobuf::uint32 PiHeader::messageid() const {
  return messageid_;
}
inline void PiHeader::set_messageid(::google::protobuf::uint32 value) {
  set_has_messageid();
  messageid_ = value;
}

// optional uint32 flags = 4;
inline bool PiHeader::has_flags() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PiHeader::set_has_flags() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PiHeader::clear_has_flags() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PiHeader::clear_flags() {
  flags_ = 0u;
  clear_has_flags();
}
inline ::google::protobuf::uint32 PiHeader::flags() const {
  return flags_;
}
inline void PiHeader::set_flags(::google::protobuf::uint32 value) {
  set_has_flags();
  flags_ = value;
}

// optional bool successResponse = 5;
inline bool PiHeader::has_successresponse() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PiHeader::set_has_successresponse() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PiHeader::clear_has_successresponse() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PiHeader::clear_successresponse() {
  successresponse_ = false;
  clear_has_successresponse();
}
inline bool PiHeader::successresponse() const {
  return successresponse_;
}
inline void PiHeader::set_successresponse(bool value) {
  set_has_successresponse();
  successresponse_ = value;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_PiHeader_2eproto__INCLUDED