
(cl:in-package :asdf)

(defsystem "demo_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Student" :depends-on ("_package_Student"))
    (:file "_package_Student" :depends-on ("_package"))
    (:file "Team" :depends-on ("_package_Team"))
    (:file "_package_Team" :depends-on ("_package"))
    (:file "Team2" :depends-on ("_package_Team2"))
    (:file "_package_Team2" :depends-on ("_package"))
    (:file "Team3" :depends-on ("_package_Team3"))
    (:file "_package_Team3" :depends-on ("_package"))
    (:file "Team4" :depends-on ("_package_Team4"))
    (:file "_package_Team4" :depends-on ("_package"))
  ))