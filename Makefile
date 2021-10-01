MSG = Default commit message
#MSG="message" to change message

git:
	git add .
	git commit -m "$(MSG)"
	git push
