(defun check_constant (str_list str_indx check)
    (if (< str_indx (list-length str_list))
        (progn
            (if (char= (nth str_indx str_list) (char check 0))
                (progn
                    (if (> (length check) 1)
                        (progn
                            (setq rtrn (check_constant str_list (+ 1 str_indx) (subseq check 1)))
                            (if (> rtrn 0)
                                (+ 1 rtrn)
                                0
                            )
                        )
                        1
                    )
                )
                0
            )
        )
        0
    )
)

(defun check_comment_ending (str_list str_indx)
    (if (< str_indx (list-length str_list))
        (if (char= (nth str_indx str_list) #\linefeed )
            1
            (+ 1 (check_comment_ending str_list (+ 1 str_indx)))
        )
        0
    )
)

(defun check_value (str_list str_indx)
    (if (< str_indx (list-length str_list))
        (if (digit-char-p (nth str_indx str_list))
            (+ 1 (check_value str_list (+ 1 str_indx)))
            0
        )
        0
    )
)

(defun check_identifier (str_list str_indx)
    (if (< str_indx (list-length str_list))
        (if (or (alpha-char-p (nth str_indx str_list)) (digit-char-p (nth str_indx str_list)))
            (+ 1 (check_identifier str_list (+ 1 str_indx)))
            0
        )
        0
    )
)

(defun control_identifier (str_list indx jmp str_out fp_out)
    (when (eq jmp 0)
        (setq jmp (check_identifier str_list indx))
        (when (> jmp 0)
            (if (digit-char-p (nth indx str_list))
                (format fp_out "ERROR - identifier starting with digit~%")
                (format fp_out str_out)
            )
        )
    )
    jmp
)

(defun control_value (str_list indx jmp str_out fp_out)
    (when (eq jmp 0)
        (setq jmp (check_value str_list indx))
        (when (> jmp 0)
            (setq next_char_indx (+ jmp indx))
            (if (and (< next_char_indx (list-length str_list)) (alpha-char-p (nth next_char_indx str_list)))
                (setq jmp 0)
                (cond 
                    ((> jmp 1)
                        (if (char= (nth indx str_list) #\0 )
                            (format fp_out "ERROR - value starting with 0~%")
                            (format fp_out str_out)
                        )
                    )
                    ((= jmp 1)
                        (format fp_out str_out)
                    )
                )
            )
        )
    )
    jmp
)

(defun control_comment (str_list indx jmp str_check str_out fp_out)
    (when (and 
            (eq jmp 0) 
            (char= (nth indx str_list) (char str_check 0))
            (< (+ 1 indx) (list-length str_list))
            (char= (nth (+ 1 indx) str_list) (char str_check 1))
        )  
        (setq jmp (check_comment_ending str_list indx))
        (format fp_out str_out)
    )
    jmp
)

(defun control_string (str_list indx jmp str_check str_out fp_out)
    (when (eq jmp 0) 
        (setq jmp (check_constant str_list indx str_check))
        (when (> jmp 0) 
            (setq next_char_indx (+ jmp indx))
            (if (< next_char_indx (list-length str_list))
                (progn
                    (if (or (alpha-char-p (nth next_char_indx str_list)) (digit-char-p (nth next_char_indx str_list)))
                        (setq jmp 0)
                        (format fp_out str_out)
                    )
                )
                (format fp_out str_out)
            )
        )
    )
    jmp
)

(defun control_operator (str_list indx jmp str_check str_out fp_out)
    (when (eq jmp 0) 
        (setq jmp (check_constant str_list indx str_check))
        (when (> jmp 0) (format fp_out str_out))
    )
    jmp
)

(defun control_else (jmp str_out fp_out)
    (when (eq jmp 0)
        (setq jmp 1)
        (format fp_out str_out)
    )
    jmp
)

(defun lexer (str_list fp_out)
    (setq indx 0)
    (loop while (< indx (length str_list)) do
        (setq jmp 0)
        (setq jmp (control_string str_list indx jmp "and" "KW_AND~%" fp_out))
        (setq jmp (control_string str_list indx jmp "or" "KW_OR~%" fp_out))
        (setq jmp (control_string str_list indx jmp "not" "KW_NOT~%" fp_out))
        (setq jmp (control_string str_list indx jmp "equal" "KW_EQUAL~%" fp_out))
        (setq jmp (control_string str_list indx jmp "less" "KW_LESS~%" fp_out))
        (setq jmp (control_string str_list indx jmp "nil" "KW_NIL~%" fp_out))
        (setq jmp (control_string str_list indx jmp "list" "KW_LIST~%" fp_out))
        (setq jmp (control_string str_list indx jmp "append" "KW_APPEND~%" fp_out))
        (setq jmp (control_string str_list indx jmp "concat" "KW_CONCAT~%" fp_out))
        (setq jmp (control_string str_list indx jmp "set" "KW_SET~%" fp_out))
        (setq jmp (control_string str_list indx jmp "deffun" "KW_DEFFUN~%" fp_out))
        (setq jmp (control_string str_list indx jmp "for" "KW_FOR~%" fp_out))
        (setq jmp (control_string str_list indx jmp "if" "KW_IF~%" fp_out))
        (setq jmp (control_string str_list indx jmp "exit" "KW_EXIT~%" fp_out))
        (setq jmp (control_string str_list indx jmp "load" "KW_LOAD~%" fp_out))
        (setq jmp (control_string str_list indx jmp "disp" "KW_DISP~%" fp_out))
        (setq jmp (control_string str_list indx jmp "true" "KW_TRUE~%" fp_out))
        (setq jmp (control_string str_list indx jmp "false" "KW_FALSE~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "+" "OP_PLUS~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "-" "OP_MINUS~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "/" "OP_DIV~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "*" "OP_MULT~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "(" "OP_OP~%" fp_out))
        (setq jmp (control_operator str_list indx jmp ")" "OP_CP~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "**" "OP_DBLMULT~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "\"" "OP_C~%" fp_out))
        (setq jmp (control_operator str_list indx jmp "," "OP_COMMA~%" fp_out))
        (setq jmp (control_comment str_list indx jmp ";;" "COMMENT~%" fp_out))

        (setq jmp (control_value str_list indx jmp "VALUE~%" fp_out))
        (setq jmp (control_identifier str_list indx jmp "IDENTIFIER~%" fp_out))

        (setq jmp (control_operator str_list indx jmp " " "" fp_out))
        (setq jmp (control_operator str_list indx jmp (string #\tab) "" fp_out))
        (setq jmp (control_operator str_list indx jmp (string #\linefeed) "" fp_out))
        (setq jmp (control_else jmp "ERROR - character could not be resolved~%" fp_out))
        (setq indx (+ indx jmp))
    )
)

(defun gppinterpreter ()
    (with-open-file (fp_out "parsed_lisp.txt" 
    :direction :output 
    :if-exists :supersede 
    :if-does-not-exist :create )
        (defvar str_list ())
        (if (eq *args* nil)
            (progn
                (loop
                    (setq strng_in (read-line))
                    (when (eq (length strng_in) 0) (return))
                    (with-input-from-string (strm_in strng_in)
                        (loop for temp_char = (read-char strm_in nil) while temp_char do
                            (setq str_list (append str_list (list temp_char)))
                        )
                    )
                    (setq str_list (append str_list (list #\linefeed )))
                )
            )
            (progn
                (with-open-file (fp_in (elt *args* 0)
                :direction :input )
                    (loop for temp_char = (read-char fp_in nil) while temp_char do
                        (setq str_list (append str_list (list temp_char)))
                    )
                )
            )
        )

        (lexer str_list fp_out)
        ;(princ str_list fp_out)
    )
)

(gppinterpreter )