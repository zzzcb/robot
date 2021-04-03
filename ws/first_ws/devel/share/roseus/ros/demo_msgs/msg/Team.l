;; Auto-generated. Do not edit!


(when (boundp 'demo_msgs::Team)
  (if (not (find-package "DEMO_MSGS"))
    (make-package "DEMO_MSGS"))
  (shadow 'Team (find-package "DEMO_MSGS")))
(unless (find-package "DEMO_MSGS::TEAM")
  (make-package "DEMO_MSGS::TEAM"))

(in-package "ROS")
;;//! \htmlinclude Team.msg.html


(defclass demo_msgs::Team
  :super ros::object
  :slots (_name _leader ))

(defmethod demo_msgs::Team
  (:init
   (&key
    ((:name __name) "")
    ((:leader __leader) (instance demo_msgs::Student :init))
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _leader __leader)
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
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; demo_msgs/Student _leader
    (send _leader :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;; demo_msgs/Student _leader
       (send _leader :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; demo_msgs/Student _leader
     (send _leader :deserialize buf ptr-) (incf ptr- (send _leader :serialization-length))
   ;;
   self)
  )

(setf (get demo_msgs::Team :md5sum-) "fc6db864ca434163aea808e9b625a07c")
(setf (get demo_msgs::Team :datatype-) "demo_msgs/Team")
(setf (get demo_msgs::Team :definition-)
      "string name
Student leader

================================================================================
MSG: demo_msgs/Student
string name
int32 age

")



(provide :demo_msgs/Team "fc6db864ca434163aea808e9b625a07c")


