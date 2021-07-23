(defun read_file (file_name)
  (defvar temp_list ())
  (with-open-file (file file_name)
    (loop for expression = (read file nil) while expression do
      (setq temp_list (append temp_list (list expression)))
    )
  )
  temp_list
)

(defun flatten (src_list)
  (defvar flat_list ())
  (loop for index = 0 while (not (eq nil src_list)) do
    (if (typep (nth 0 src_list) 'list)
      (setq src_list (append (nth 0 src_list) (cdr src_list)))
      (setq flat_list (append flat_list (list (pop src_list))))
    )
  )
  flat_list
)

(defun write_file (file_name src_list)
  (with-open-file (file file_name 
  :direction :output 
  :if-exists :supersede 
  :if-does-not-exist :create)
    (princ src_list file)
  )
)

(defvar *list* (read_file "nested_list.txt"))

(format t "In:  ~a~%" *list*)
(setq *list* (flatten *list*))
(format t "Out: ~a~%" *list*)

(write_file "flattened_list.txt" *list*)
