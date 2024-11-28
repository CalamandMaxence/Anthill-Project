rendu: normalize archive

normalize: 
	astyle -A8 -s4 --suffix=none --recursive '*.cpp' '*.hpp'

archive:
	@echo "====================================================="
	@echo "           MERCI DE CONTROLER LE CONTENU CI-DESSOUS  "
	@echo "              PLEASE CHECK THE CONTENT BELOW         "
	@echo "====================================================="
	@zip -r ant-${GROUPE}.zip SCIPER* JOURNAL* README* REPONSES* \
	partie?/src partie*/extlib partie*/res  \
	-x '*/gmon.out' -x '*/*~' -x '*/.svn/*' -x '*/core' -x '*/*.zip'\
	-x '*/*.orig' -x '*/.git/*' -x '*/build*/*' -x '*/*.o' \
	-x '*/*CMakeLists.txt.user*' -x '*/.DS_Store*' 
	@echo "L'ARCHIVE ant-${GROUPE}.zip EST CONSTRUITE"
	@echo "MERCI DE LA CONTROLER AVANT DE LA SOUMETTRE SUR MOODLE"
	@du -h ant-${GROUPE}.zip