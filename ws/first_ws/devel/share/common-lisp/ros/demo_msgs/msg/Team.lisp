; Auto-generated. Do not edit!


(cl:in-package demo_msgs-msg)


;//! \htmlinclude Team.msg.html

(cl:defclass <Team> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (leader
    :reader leader
    :initarg :leader
    :type demo_msgs-msg:Student
    :initform (cl:make-instance 'demo_msgs-msg:Student)))
)

(cl:defclass Team (<Team>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Team>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Team)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name demo_msgs-msg:<Team> is deprecated: use demo_msgs-msg:Team instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <Team>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:name-val is deprecated.  Use demo_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'leader-val :lambda-list '(m))
(cl:defmethod leader-val ((m <Team>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:leader-val is deprecated.  Use demo_msgs-msg:leader instead.")
  (leader m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Team>) ostream)
  "Serializes a message object of type '<Team>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'leader) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Team>) istream)
  "Deserializes a message object of type '<Team>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'leader) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Team>)))
  "Returns string type for a message object of type '<Team>"
  "demo_msgs/Team")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Team)))
  "Returns string type for a message object of type 'Team"
  "demo_msgs/Team")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Team>)))
  "Returns md5sum for a message object of type '<Team>"
  "fc6db864ca434163aea808e9b625a07c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Team)))
  "Returns md5sum for a message object of type 'Team"
  "fc6db864ca434163aea808e9b625a07c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Team>)))
  "Returns full string definition for message of type '<Team>"
  (cl:format cl:nil "string name~%Student leader~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Team)))
  "Returns full string definition for message of type 'Team"
  (cl:format cl:nil "string name~%Student leader~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Team>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'leader))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Team>))
  "Converts a ROS message object to a list"
  (cl:list 'Team
    (cl:cons ':name (name msg))
    (cl:cons ':leader (leader msg))
))
