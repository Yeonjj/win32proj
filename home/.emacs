
;; color themes
(load-file "/home/.emacs.d/themes/gruvbox-dark-theme.el")
;; remove scroll bar
(scroll-bar-mode -1)
;; disable tool bar
(tool-bar-mode -1)
;; tabsize
(setq-default c-basic-offset 8
                 tab-width 8
                 indent-tabs-mode t)


; setting very high limits for undo buffers
(setq undo-limit 20000000)
(setq undo-strong-limit 40000000)

; Bright-red TODOs
 (setq fixme-modes '(c++-mode c-mode emacs-lisp-mode))
 (make-face 'font-lock-fixme-face)
 (make-face 'font-lock-note-face)
 (mapc (lambda (mode)
	 (font-lock-add-keywords
	  mode
	  '(("\\<\\(TODO\\)" 1 'font-lock-fixme-face t)
            ("\\<\\(NOTE\\)" 1 'font-lock-note-face t))))
	fixme-modes)
 (modify-face 'font-lock-fixme-face "Red" nil nil t nil t nil nil)
 (modify-face 'font-lock-note-face "Dark Green" nil nil t nil t nil nil)

; Setup my compilation mode
(defun casey-big-fun-compilation-hook ()
  (make-local-variable 'truncate-lines)
  (setq truncate-lines nil)
)

(add-hook 'compilation-mode-hook 'casey-big-fun-compilation-hook)

(defun load-todo ()
  (interactive)
  (find-file casey-todo-file)
)
(define-key global-map "\et" 'load-todo)

(defun insert-timeofday ()
   (interactive "*")
   (insert (format-time-string "---------------- %a, %d %b %y: %I:%M%p")))
(defun load-log ()
  (interactive)
  (find-file casey-log-file)
  (if (boundp 'longlines-mode) ()
    (longlines-mode 1)
    (longlines-show-hard-newlines))
  (if (equal longlines-mode t) ()
    (longlines-mode 1)
    (longlines-show-hard-newlines))
  (end-of-buffer)
  (newline-and-indent)
  (insert-timeofday)
  (newline-and-indent)
  (newline-and-indent)
  (end-of-buffer)
)
(define-key global-map "\eT" 'load-log)


(require 'package) 
(add-to-list 'package-archives
             '("melpa" . "https://melpa.org/packages/"))
(when (< emacs-major-version 24)
  (add-to-list 'package-archives '("gnu" . "http://elpa.gnu.org/packages/")))
(package-initialize) 

;auto-complete
(add-to-list 'load-path
              "~/.emacs.d/auto-complete-1.5.1")
(require 'auto-complete)
(require 'auto-complete-config)
(ac-config-default)


;yasnippet
(add-to-list 'load-path
              "~/.emacs.d/elpa/yasnippet-0.9.1")
(require 'yasnippet)
(yas-global-mode 1)
