#include "bmp.h"

char* _strdup(char *s){
	return strcpy(malloc(sizeof(*s) * (strlen(s) + 1)), s);
}

bool _fileIntegCheck(FILE *fp){
	BMPHeader checkHdr;
	if(fread(&checkHdr, sizeof(checkHdr),1,fp) != 1){
		return false;
	}
	fseek(fp,0,SEEK_SET);
	if(fread(&checkHdr.type, sizeof(checkHdr.type),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.size, sizeof(checkHdr.size),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.reserved1, sizeof(checkHdr.reserved1),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.reserved2, sizeof(checkHdr.reserved2),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.offset, sizeof(checkHdr.offset),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.dib_header_size, sizeof(checkHdr.dib_header_size), 1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.width_px, sizeof(checkHdr.width_px),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.height_px, sizeof(checkHdr.height_px),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.num_planes, sizeof(checkHdr.num_planes),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.bits_per_pixel, sizeof(checkHdr.bits_per_pixel), 1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.compression, sizeof(checkHdr.compression),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.image_size_bytes, sizeof(checkHdr.image_size_bytes),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.x_resolution_ppm, sizeof(checkHdr.x_resolution_ppm),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.y_resolution_ppm,sizeof(checkHdr.y_resolution_ppm),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.num_colors, sizeof(checkHdr.num_colors),1,fp) != 1){
		return false;
	}
	if(fread(&checkHdr.important_colors, sizeof(checkHdr.important_colors),1,fp) != 1){
		return false;
	}
	fseek(fp,0,SEEK_SET);
	return true;
}

bool check_bmp_header(BMPHeader *bmp_hdr, FILE *fp){
	if(fp == NULL){
		return false;
	}
	if(bmp_hdr -> type != 0x4d42){
		return false;
	}
	if(bmp_hdr -> offset != BMP_HEADER_SIZE){
		return false;
	}
	if(bmp_hdr -> dib_header_size != DIB_HEADER_SIZE){
		return false;
	}
	if(bmp_hdr -> num_planes != 1){
		return false;
	}
	if(bmp_hdr -> compression != 0){
		return false;
	}
	if(bmp_hdr -> num_colors != 0){
		return false;
	}
	if(bmp_hdr -> important_colors != 0){
		return false;
	}
	if(bmp_hdr -> bits_per_pixel != 24){
		if(bmp_hdr -> bits_per_pixel != 16){
			return false;
		}
	}
	if(bmp_hdr -> image_size_bytes != bmp_hdr -> size - BMP_HEADER_SIZE){
		return false;
	}
	fseek(fp,0,SEEK_END);
	int fsz = ftell(fp);
	if(bmp_hdr -> size != fsz){
		return false;
	}
	if(bmp_hdr -> image_size_bytes != fsz - BMP_HEADER_SIZE){
		return false;
	}
	int width_bytes = ((bmp_hdr -> width_px) * (bmp_hdr -> bits_per_pixel) / 8);
	int padding = 4 - width_bytes % 4;
	int checkSize = (padding + width_bytes) * bmp_hdr -> height_px;
	if(checkSize != bmp_hdr -> image_size_bytes){
		return false;
	}
	fseek(fp,0,SEEK_SET);
	return _fileIntegCheck(fp);
}

BMPImage *read_bmp(FILE *fp, char **error){
	if(fp == NULL){
		*error = _strdup("File Not Found/ Empty");
		return NULL;
	}
	
	BMPImage *image = malloc(sizeof(*image));
	if(image == NULL){
		*error = _strdup("Error allocating malloc for image");
		return NULL;
	}

	if(_fileIntegCheck(fp) == false){
		*error = _strdup("Error reading the file");
		free(image);
		return NULL;
	}

	fseek(fp,0,SEEK_SET);
	if(fread(&image->header, sizeof(image->header),1,fp) != 1){
		*error = _strdup("Error reading the header of the file");
		return NULL;
	}

	if(check_bmp_header(&image->header,fp)){
		image -> data = malloc(sizeof(*(image -> data)) * image->header.image_size_bytes);
		if(image -> data == NULL){
			*error = _strdup("Error allocating memory to data");
			free(image);
			return NULL;
		}
		fseek(fp,image -> header.offset,SEEK_SET);
		if(fread(image -> data, image -> header.image_size_bytes,1,fp) != 1){
			*error = _strdup("Error reading the data");
			free(image);
			return NULL;
		}
		fseek(fp,0,SEEK_SET);
		return image;
	}
	else{
		*error = _strdup("Invalid Header");
		free(image);
		fseek(fp,0,SEEK_SET);
		return NULL;
	}
	fseek(fp,0,SEEK_SET);
	return NULL;
}

bool write_bmp(FILE *fp, BMPImage *image, char **error){
	if(fp == NULL){
		*error = _strdup("Invalid file pointer");
		return false;
	}
	if(image == NULL){
		*error = _strdup("Invalid image structure");
		return false;
	}
	
	fseek(fp,0,SEEK_SET);
	if(fwrite(&image -> header, sizeof(image -> header), 1, fp) != 1){
		*error = _strdup("Error writing the header");
		return false;
	}
	if(fwrite(image -> data, image -> header.image_size_bytes,1,fp) != 1){
		*error = _strdup("Error writing the file data");
		return false;
	}
	return true;
}

unsigned char **_twoDGRet(unsigned char * imdata, BMPHeader *header){
	unsigned char **twoDG = malloc(sizeof(*twoDG) * header -> height_px);
	int lenRow = header -> width_px * header -> bits_per_pixel / 8;
	int rowChanger = 0;
	for(int i = 0; i < header -> height_px; i++){
		twoDG[i] = malloc(sizeof(**twoDG) * lenRow);
	}

	for(int i = header -> height_px - 1; i >= 0; i--){
		for(int j = 0; j < lenRow; j++){
			twoDG[i][j] = imdata[rowChanger];
			rowChanger++;
		}
		for(int q = 0; q < header -> width_px % 4; q++){
			rowChanger++;
		}
	}
	return twoDG;
}

BMPImage *crop_bmp(BMPImage *image, int x, int y, int w, int h, char **error){
	if(image == NULL){
		*error = _strdup("Invalid input image data");
		return NULL;
	}
	
	if(w > (image -> header.width_px - x)){
		*error = _strdup("Supplied width greater than image width");
		return NULL;
	}
	if(h > (image -> header.height_px - y)){
		*error = _strdup("Supplied height greater than image height");
		return NULL;
	}

	BMPImage *cropImage = malloc(sizeof(*cropImage));
	cropImage -> header = image -> header;
	cropImage -> header.width_px = w;
	cropImage -> header.height_px = h;
	unsigned char** twoDG = _twoDGRet(image -> data, &image -> header);	
	int imsz = h * (w * image -> header.bits_per_pixel / 8 + w % 4);
	unsigned char *cropDat = malloc(sizeof(*cropDat) * imsz);
	if(cropDat == NULL){
		*error = _strdup("Cannot allocate malloc to crop data");
		return NULL;
	}
	
	int looper = 0;
	int bytesPP = image -> header.bits_per_pixel / 8;
	for(int j = y + h - 1; j >= y; j--){
		for(int k = x * bytesPP; k < (x + w) * bytesPP; k++){
			cropDat[looper++] = twoDG[j][k];
		}
		for(int k = 0; k < w % 4; k++){
			cropDat[looper++] = 0;
		}
	}

	for(int t = 0; t < image -> header.height_px; t++){
		free(twoDG[t]);
	}
	free(twoDG);
	cropImage -> data = cropDat;
	cropImage -> header.image_size_bytes = imsz;
	cropImage -> header.size = imsz + cropImage -> header.offset;
	memcpy(cropImage -> data, image -> data, sizeof(*(cropImage -> data)) * (cropImage -> header.image_size_bytes));
	return cropImage;
}

void free_bmp(BMPImage *image){
	if(image != NULL){
		if(image -> data != NULL){
			free(image -> data);
		}
		free(image);
	}
}
