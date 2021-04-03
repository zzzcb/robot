; Auto-generated. Do not edit!


(cl:in-package demo_msgs-msg)


;//! \htmlinclude Student.msg.html

(cl:defclass <Student> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform "")
   (age
    :reader age
    :initarg :age
    :type cl:integer
    :initform 0))
)

(cl:defclass Student (<Student>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Student>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Student)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name demo_msgs-msg:<Student> is deprecated: use demo_msgs-msg:Student instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <Student>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:name-val is deprecated.  Use demo_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'age-val :lambda-list '(m))
(cl:defmethod age-val ((m <Student>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:age-val is deprecated.  Use demo_msgs-msg:age instead.")
  (age m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Student>) ostream)
  "Serializes a message object of type '<Student>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (cl:let* ((signed (cl:slot-value msg 'age)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Student>) istream)
  "Deserializes a message object of type '<Student>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'age) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Student>)))
  "Returns string type for a message object of type '<Student>"
  "demo_msgs/Student")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Student)))
  "Returns string type for a message object of type 'Student"
  "demo_msgs/Student")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Student>)))
  "Returns md5sum for a message object of type '<Student>"
  "83da5ca00b8e049b0559653a472c88a5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Student)))
  "Returns md5sum for a message object of type 'Student"
  "83da5ca00b8e049b0559653a472c88a5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Student>)))
  "Returns full string definition for message of type '<Student>"
  (cl:format cl:nil "string name~%int32 age~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Student)))
  "Returns full string definition for message of type 'Student"
  (cl:format cl:nil "string name~%int32 age~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Student>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Student>))
  "Converts a ROS message object to a list"
  (cl:list 'Student
    (cl:cons ':name (name msg))
    (cl:cons ':age (age msg))
))
