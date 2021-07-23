(defstruct boundries
  b1
  b2
)

(defun read_file (file_name)
  (with-open-file (file file_name)
    (setq temp_struct 
      (make-boundries
        :b1 (read file)
        :b2 (read file)
      )
    )
  )
  temp_struct
)

(defun is_prime (num)
  (if (< num 2) 
    nil
    (progn
      (setq res t)
      (setq i 2)
      (loop while (and (<= i (isqrt num)) res) do
        (when (= 0 (mod num i)) (setq res nil))
        (setq i (+ i 1))
      )
      res
    )
  )
)

(defun is_semi_prime (num)
  (if (< num 2)
    nil
    (progn
      (setq div1 2)
      (loop while (and (<= div1 (isqrt num)) (/= 0 (mod num div1))) do
        (setq div1 (+ div1 1))
      )
      (setq div2 (/ num div1))
      (if (is_prime div2)
        t
        nil
      )
    )
  )
)

(defun primecrawler (read_file_name write_file_name)
  (setq nums_list ())
  (setq bndrs (read_file read_file_name))
  (loop for i from (boundries-b1 bndrs) to (boundries-b2 bndrs) do
    (cond 
      ((is_prime i) (setq nums_list (append nums_list (list (concatenate 'string (write-to-string i) " is Prime")))))
      ((is_semi_prime i) (setq nums_list (append nums_list (list (concatenate 'string (write-to-string i) " is Semi-prime")))))
    )
  )
  (write_file write_file_name nums_list)
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

(primecrawler "boundries.txt" "primedistribution.txt")
