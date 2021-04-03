;; Auto-generated. Do not edit!


(when (boundp 'demo_msgs::Team2)
  (if (not (find-package "DEMO_MSGS"))
    (make-package "DEMO_MSGS"))
  (shadow 'Team2 (find-package "DEMO_MSGS")))
(unless (find-package "DEMO_MSGS::TEAM2")
  (make-package "DEMO_MSGS::TEAM2"))

(in-package "ROS")
;;//! \htmlinclude Team2.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass demo_msgs::Team2
  :super ros::object
  :slots (_name _leader _intro ))

(defmethod demo_msgs::Team2
  (:init
   (&key
    ((:name __name) "")
    ((:leader __leader) (instance demo_msgs::Student :init))
    ((:intro __intro) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _name (string __name))
   (setq _leader __leader)
   (setq _intro __intro)
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
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ;; demo_msgs/Student _leader
    (send _leader :serialization-length)
    ;; std_msgs/String _intro
    (send _intro :serialization-length)
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
   ;;
   self)
  )

(setf (get demo_msgs::Team2 :md5sum-) "8d49b9b867129a9e436a004b0d6e3743")
(setf (get demo_msgs::Team2 :datatype-) "demo_msgs/Team2")
(setf (get demo_msgs::Team2 :definition-)
      "string name
Student leader 
std_msgs/String intro

================================================================================
MSG: demo_msgs/Student
string name
int32 age

================================================================================
MSG: std_msgs/String
string data

")



(provide :demo_msgs/Team2 "8d49b9b867129a9e436a004b0d6e3743")


