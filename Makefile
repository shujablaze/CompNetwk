.PHONY: clean All

All:
	@echo "----------Building project:[ CnLab - Debug ]----------"
	@cd "D:\oopsLab\CnLab\CnLab" && "$(MAKE)" -f  "CnLab.mk"
clean:
	@echo "----------Cleaning project:[ CnLab - Debug ]----------"
	@cd "D:\oopsLab\CnLab\CnLab" && "$(MAKE)" -f  "CnLab.mk" clean
