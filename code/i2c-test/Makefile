TARGET=test
SOURCE=$(TARGET).c
CC=/home/olivier/Documents/School/Bachelorproef/custom-linux/buildroot-2016.11.2/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-gcc

$(TARGET): $(SOURCE)
	@echo "making $(SOURCE)"
	$(CC) -o $(TARGET) $(SOURCE)


install: $(TARGET)
	scp $(TARGET) olivier@192.168.0.108:/home/olivier

clean:
	-rm $(TARGET)