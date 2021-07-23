(defun read_file (file_name)
  (setq temp_list ())
  (with-open-file (file file_name)
    (setq i 0)
    (loop for expression = (read file nil) while (and expression (< i 5)) do
      (setq temp_list (append temp_list (list expression)))
      (setq i (+ i 1))
    )
  )
  temp_list
)

(defun collatz_sequence_output (num)
  (if (eq 0 (mod num 2))
    (when (/= num 1) (concatenate 'string " " (write-to-string num) (collatz_sequence_output (/ num 2))))
    (when (/= num 1) (concatenate 'string " " (write-to-string num) (collatz_sequence_output (+ 1 (* num 3)))))
  )
)

(defun collatz_sequence (read_file_name write_file_name)
  (setq col_list (read_file read_file_name))
  (setq col_list_out ())
  (dolist (i col_list) 
    (setq col_list_out (append col_list_out (list (concatenate 'string (write-to-string i) ":" (collatz_sequence_output i)))))
  )
  (write_file write_file_name col_list_out)
)

(defun write_file (file_name src_list)
  (with-open-file (file file_name 
  :direction :output 
  :if-exists :supersede 
  :if-does-not-exist :create)
    (dolist (i src_list)
      (format file "~a~%" i)
    )
  )
)

(collatz_sequence "integer_inputs.txt" "collatz_outputs.txt")