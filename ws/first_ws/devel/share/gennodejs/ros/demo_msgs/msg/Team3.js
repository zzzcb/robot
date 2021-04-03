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
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Team3 {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
      this.leader = null;
      this.intro = null;
      this.location = null;
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
      if (initObj.hasOwnProperty('intro')) {
        this.intro = initObj.intro
      }
      else {
        this.intro = new std_msgs.msg.String();
      }
      if (initObj.hasOwnProperty('location')) {
        this.location = initObj.location
      }
      else {
        this.location = new geometry_msgs.msg.Twist();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Team3
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    // Serialize message field [leader]
    bufferOffset = Student.serialize(obj.leader, buffer, bufferOffset);
    // Serialize message field [intro]
    bufferOffset = std_msgs.msg.String.serialize(obj.intro, buffer, bufferOffset);
    // Serialize message field [location]
    bufferOffset = geometry_msgs.msg.Twist.serialize(obj.location, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Team3
    let len;
    let data = new Team3(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [leader]
    data.leader = Student.deserialize(buffer, bufferOffset);
    // Deserialize message field [intro]
    data.intro = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    // Deserialize message field [location]
    data.location = geometry_msgs.msg.Twist.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.name.length;
    length += Student.getMessageSize(object.leader);
    length += std_msgs.msg.String.getMessageSize(object.intro);
    return length + 52;
  }

  static datatype() {
    // Returns string type for a message object
    return 'demo_msgs/Team3';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f57c072b89f0cdd1735089d396821dae';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string name
    Student leader 
    std_msgs/String intro
    geometry_msgs/Twist location 
    
    ================================================================================
    MSG: demo_msgs/Student
    string name
    int32 age
    
    ================================================================================
    MSG: std_msgs/String
    string data
    
    ================================================================================
    MSG: geometry_msgs/Twist
    # This expresses velocity in free space broken into its linear and angular parts.
    Vector3  linear
    Vector3  angular
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Team3(null);
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

    if (msg.intro !== undefined) {
      resolved.intro = std_msgs.msg.String.Resolve(msg.intro)
    }
    else {
      resolved.intro = new std_msgs.msg.String()
    }

    if (msg.location !== undefined) {
      resolved.location = geometry_msgs.msg.Twist.Resolve(msg.location)
    }
    else {
      resolved.location = new geometry_msgs.msg.Twist()
    }

    return resolved;
    }
};

module.exports = Team3;
