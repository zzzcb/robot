; Auto-generated. Do not edit!


(cl:in-package demo_msgs-msg)


;//! \htmlinclude Team3.msg.html

(cl:defclass <Team3> (roslisp-msg-protocol:ros-message)
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
    :initform (cl:make-instance 'std_msgs-msg:String))
   (location
    :reader location
    :initarg :location
    :type geometry_msgs-msg:Twist
    :initform (cl:make-instance 'geometry_msgs-msg:Twist)))
)

(cl:defclass Team3 (<Team3>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Team3>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Team3)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name demo_msgs-msg:<Team3> is deprecated: use demo_msgs-msg:Team3 instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <Team3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:name-val is deprecated.  Use demo_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'leader-val :lambda-list '(m))
(cl:defmethod leader-val ((m <Team3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:leader-val is deprecated.  Use demo_msgs-msg:leader instead.")
  (leader m))

(cl:ensure-generic-function 'intro-val :lambda-list '(m))
(cl:defmethod intro-val ((m <Team3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:intro-val is deprecated.  Use demo_msgs-msg:intro instead.")
  (intro m))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <Team3>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:location-val is deprecated.  Use demo_msgs-msg:location instead.")
  (location m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Team3>) ostream)
  "Serializes a message object of type '<Team3>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'leader) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'intro) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'location) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Team3>) istream)
  "Deserializes a message object of type '<Team3>"
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
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'location) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Team3>)))
  "Returns string type for a message object of type '<Team3>"
  "demo_msgs/Team3")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Team3)))
  "Returns string type for a message object of type 'Team3"
  "demo_msgs/Team3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Team3>)))
  "Returns md5sum for a message object of type '<Team3>"
  "f57c072b89f0cdd1735089d396821dae")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Team3)))
  "Returns md5sum for a message object of type 'Team3"
  "f57c072b89f0cdd1735089d396821dae")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Team3>)))
  "Returns full string definition for message of type '<Team3>"
  (cl:format cl:nil "string name~%Student leader ~%std_msgs/String intro~%geometry_msgs/Twist location ~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Team3)))
  "Returns full string definition for message of type 'Team3"
  (cl:format cl:nil "string name~%Student leader ~%std_msgs/String intro~%geometry_msgs/Twist location ~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Team3>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'leader))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'intro))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'location))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Team3>))
  "Converts a ROS message object to a list"
  (cl:list 'Team3
    (cl:cons ':name (name msg))
    (cl:cons ':leader (leader msg))
    (cl:cons ':intro (intro msg))
    (cl:cons ':location (location msg))
))
