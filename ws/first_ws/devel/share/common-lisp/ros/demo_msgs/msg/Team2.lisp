; Auto-generated. Do not edit!


(cl:in-package demo_msgs-msg)


;//! \htmlinclude Team2.msg.html

(cl:defclass <Team2> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (leader
    :reader leader
    :initarg :leader
    :type demo_msgs-msg:Student
    :initform (cl:make-instance 'demo_msgs-msg:Student))
   (intro
    :reader intro
    :initarg :intro
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass Team2 (<Team2>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Team2>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Team2)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name demo_msgs-msg:<Team2> is deprecated: use demo_msgs-msg:Team2 instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <Team2>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:name-val is deprecated.  Use demo_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'leader-val :lambda-list '(m))
(cl:defmethod leader-val ((m <Team2>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:leader-val is deprecated.  Use demo_msgs-msg:leader instead.")
  (leader m))

(cl:ensure-generic-function 'intro-val :lambda-list '(m))
(cl:defmethod intro-val ((m <Team2>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:intro-val is deprecated.  Use demo_msgs-msg:intro instead.")
  (intro m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Team2>) ostream)
  "Serializes a message object of type '<Team2>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'leader) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'intro) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Team2>) istream)
  "Deserializes a message object of type '<Team2>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'leader) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'intro) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Team2>)))
  "Returns string type for a message object of type '<Team2>"
  "demo_msgs/Team2")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Team2)))
  "Returns string type for a message object of type 'Team2"
  "demo_msgs/Team2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Team2>)))
  "Returns md5sum for a message object of type '<Team2>"
  "8d49b9b867129a9e436a004b0d6e3743")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Team2)))
  "Returns md5sum for a message object of type 'Team2"
  "8d49b9b867129a9e436a004b0d6e3743")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Team2>)))
  "Returns full string definition for message of type '<Team2>"
  (cl:format cl:nil "string name~%Student leader ~%std_msgs/String intro~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Team2)))
  "Returns full string definition for message of type 'Team2"
  (cl:format cl:nil "string name~%Student leader ~%std_msgs/String intro~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Team2>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'leader))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'intro))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Team2>))
  "Converts a ROS message object to a list"
  (cl:list 'Team2
    (cl:cons ':name (name msg))
    (cl:cons ':leader (leader msg))
    (cl:cons ':intro (intro msg))
))
