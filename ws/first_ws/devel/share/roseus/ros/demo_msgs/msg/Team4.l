;; Auto-generated. Do not edit!


(when (boundp 'demo_msgs::Team4)
  (if (not (find-package "DEMO_MSGS"))
    (make-package "DEMO_MSGS"))
  (shadow 'Team4 (find-package "DEMO_MSGS")))
(unless (find-package "DEMO_MSGS::TEAM4")
  (make-package "DEMO_MSGS::TEAM4"))

(in-package "ROS")
;;//! \htmlinclude Team4.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass demo_msgs::Team4
  :super ros::object
  :slots (_name _leader _intro _location _members ))

(defmethod demo_msgs::Team4
  (:init
   (&key
    ((:name __name) "")
    ((:leader __leader) (instance demo_msgs::Student :init))
    ((:intro __intro) (instance std_msgs::String :init))
    ((:location __location) (instance geometry_msgs::Twist :init))
    ((:members __members) (let (r) (dotimes (i 0) (push (instance demo_msgs::Student :init) r)) r))
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _leader __leader)
   (setq _intro __intro)
   (setq _location __location)
   (setq _members __members)
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:leader
   (&rest __leader)
   (if (keywordp (car __leader))
       (send* _leader __leader)
     (progn
       (if __leader (setq _leader (car __leader)))
       _leader)))
  (:intro
   (&rest __intro)
   (if (keywordp (car __intro))
       (send* _intro __intro)
     (progn
       (if __intro (setq _intro (car __intro)))
       _intro)))
  (:location
   (&rest __location)
   (if (keywordp (car __location))
       (send* _location __location)
     (progn
       (if __location (setq _location (car __location)))
       _location)))
  (:members
   (&rest __members)
   (if (keywordp (car __members))
       (send* _members __members)
     (progn
       (if __members (setq _members (car __members)))
       _members)))
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; demo_msgs/Student _leader
    (send _leader :serialization-length)
    ;; std_msgs/String _intro
    (send _intro :serialization-length)
    ;; geometry_msgs/Twist _location
    (send _location :serialization-length)
    ;; demo_msgs/Student[] _members
    (apply #'+ (send-all _members :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; demo_msgs/Student _leader
       (send _leader :serialize s)
     ;; std_msgs/String _intro
       (send _intro :serialize s)
     ;; geometry_msgs/Twist _location
       (send _location :serialize s)
     ;; demo_msgs/Student[] _members
     (write-long (length _members) s)
     (dolist (elem _members)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; demo_msgs/Student _leader
     (send _leader :deserialize buf ptr-) (incf ptr- (send _leader :serialization-length))
   ;; std_msgs/String _intro
     (send _intro :deserialize buf ptr-) (incf ptr- (send _intro :serialization-length))
   ;; geometry_msgs/Twist _location
     (send _location :deserialize buf ptr-) (incf ptr- (send _location :serialization-length))
   ;; demo_msgs/Student[] _members
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _members (let (r) (dotimes (i n) (push (instance demo_msgs::Student :init) r)) r))
     (dolist (elem- _members)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get demo_msgs::Team4 :md5sum-) "ccc100d1d4c1606945bd893da4b64a28")
(setf (get demo_msgs::Team4 :datatype-) "demo_msgs/Team4")
(setf (get demo_msgs::Team4 :definition-)
      "string name
Student leader 
std_msgs/String intro
geometry_msgs/Twist location 
Student[] members

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
")



(provide :demo_msgs/Team4 "ccc100d1d4c1606945bd893da4b64a28")


