// Auto-generated. Do not edit!

// (in-package demo_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Student = require('./Student.js');

//-----------------------------------------------------------

class Team {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
      this.leader = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
      if (initObj.hasOwnProperty('leader')) {
        this.leader = initObj.leader
      }
      else {
        this.leader = new Student();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Team
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    // Serialize message field [leader]
    bufferOffset = Student.serialize(obj.leader, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Team
    let len;
    let data = new Team(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [leader]
    data.leader = Student.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.name.length;
    length += Student.getMessageSize(object.leader);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'demo_msgs/Team';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fc6db864ca434163aea808e9b625a07c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string name
    Student leader
    
    ================================================================================
    MSG: demo_msgs/Student
    string name
    int32 age
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Team(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    if (msg.leader !== undefined) {
      resolved.leader = Student.Resolve(msg.leader)
    }
    else {
      resolved.leader = new Student()
    }

    return resolved;
    }
};

module.exports = Team;
