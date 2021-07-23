(defstruct huffman_node
  char_code
  freq
  left
  right
)

(defun huffman_input_list_insert (src_list char_in)
  (setq found nil)
  (dolist (i src_list)
    (when (eq (huffman_node-char_code i) char_in) 
      (setf (huffman_node-freq i) (+ (huffman_node-freq i) 1))
      (setq found t)
    )
  )
  (when (not found)
    (setq temp_node 
      (make-huffman_node
        :char_code char_in
        :freq 1
        :left nil
        :right nil
      )
    )
    (push temp_node src_list)
  )
  src_list
)

(defun read_file (file_name)
  (defvar temp_list ())
  (with-open-file (file file_name)
    (loop for chr = (read-char file nil) while chr do
      (setq temp_list (huffman_input_list_insert temp_list chr))
    )
  )
  temp_list
)

(defun build_huffman_tree (src_list)
  (if (< 1 (list-length src_list))
    (progn
      (sort src_list #'< :key #'huffman_node-freq)
      (setq left_node (pop src_list))
      (setq right_node (pop src_list))
      (setq temp_node 
        (make-huffman_node
          :char_code nil
          :freq (+ (huffman_node-freq left_node) (huffman_node-freq right_node))
          :left left_node
          :right right_node
        )
      )
      (push temp_node src_list)
      (build_huffman_tree src_list)
    )
    (car src_list)
  )
)

(defun huffman_tree_to_str_list (node &optional (str ""))
  (cond 
    ((eq node nil) 
      nil
    )
    ((eq (huffman_node-char_code node) nil) 
      (setq temp_str_list 
        (append 
          (huffman_tree_to_str_list (huffman_node-left node) (concatenate 'string str " 0"))
          (huffman_tree_to_str_list (huffman_node-right node) (concatenate 'string str " 1"))
        )
      )
      temp_str_list
    )
    (
      (if (eq #\linefeed (huffman_node-char_code node))
        (list (concatenate 'string "\\n" ":" str))
        (list (concatenate 'string (string (huffman_node-char_code node)) ":" str))
      )
    )
  )
)

(defun cmpr (x y)
  (< (length x) (length y))
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

(defvar *list* '())
(setq *list* (read_file "paragraph.txt"))
(setq *list* (build_huffman_tree *list*))
(setq *list* (huffman_tree_to_str_list *list*))
(sort *list* #'cmpr)
(write_file "huffman_codes.txt" *list*)

(dolist (i *list*)
  (format t "~a~%" i)
)
