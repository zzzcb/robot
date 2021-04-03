; Auto-generated. Do not edit!


(cl:in-package demo_msgs-msg)


;//! \htmlinclude Team4.msg.html

(cl:defclass <Team4> (roslisp-msg-protocol:ros-message)
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
    :initform (cl:make-instance 'geometry_msgs-msg:Twist))
   (members
    :reader members
    :initarg :members
    :type (cl:vector demo_msgs-msg:Student)
   :initform (cl:make-array 0 :element-type 'demo_msgs-msg:Student :initial-element (cl:make-instance 'demo_msgs-msg:Student))))
)

(cl:defclass Team4 (<Team4>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Team4>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Team4)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name demo_msgs-msg:<Team4> is deprecated: use demo_msgs-msg:Team4 instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <Team4>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:name-val is deprecated.  Use demo_msgs-msg:name instead.")
  (name m))

(cl:ensure-generic-function 'leader-val :lambda-list '(m))
(cl:defmethod leader-val ((m <Team4>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:leader-val is deprecated.  Use demo_msgs-msg:leader instead.")
  (leader m))

(cl:ensure-generic-function 'intro-val :lambda-list '(m))
(cl:defmethod intro-val ((m <Team4>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:intro-val is deprecated.  Use demo_msgs-msg:intro instead.")
  (intro m))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <Team4>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:location-val is deprecated.  Use demo_msgs-msg:location instead.")
  (location m))

(cl:ensure-generic-function 'members-val :lambda-list '(m))
(cl:defmethod members-val ((m <Team4>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader demo_msgs-msg:members-val is deprecated.  Use demo_msgs-msg:members instead.")
  (members m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Team4>) ostream)
  "Serializes a message object of type '<Team4>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'leader) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'intro) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'location) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'members))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'members))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Team4>) istream)
  "Deserializes a message object of type '<Team4>"
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
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'members) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'members)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'demo_msgs-msg:Student))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Team4>)))
  "Returns string type for a message object of type '<Team4>"
  "demo_msgs/Team4")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Team4)))
  "Returns string type for a message object of type 'Team4"
  "demo_msgs/Team4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Team4>)))
  "Returns md5sum for a message object of type '<Team4>"
  "ccc100d1d4c1606945bd893da4b64a28")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Team4)))
  "Returns md5sum for a message object of type 'Team4"
  "ccc100d1d4c1606945bd893da4b64a28")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Team4>)))
  "Returns full string definition for message of type '<Team4>"
  (cl:format cl:nil "string name~%Student leader ~%std_msgs/String intro~%geometry_msgs/Twist location ~%Student[] members~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Team4)))
  "Returns full string definition for message of type 'Team4"
  (cl:format cl:nil "string name~%Student leader ~%std_msgs/String intro~%geometry_msgs/Twist location ~%Student[] members~%~%================================================================================~%MSG: demo_msgs/Student~%string name~%int32 age~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Team4>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'leader))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'intro))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'location))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'members) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Team4>))
  "Converts a ROS message object to a list"
  (cl:list 'Team4
    (cl:cons ':name (name msg))
    (cl:cons ':leader (leader msg))
    (cl:cons ':intro (intro msg))
    (cl:cons ':location (location msg))
    (cl:cons ':members (members msg))
))
