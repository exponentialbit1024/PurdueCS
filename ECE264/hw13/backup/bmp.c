#include "bmp.h"

bool check_bmp_header(BMPHeader *bmp_hdr, FILE *fp){
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
	if(bmp_hdr -> num_colors != 0 || bmp_hdr -> important_colors != 0){
		return false;
	}
	if(bmp_hdr -> bits_per_pixel != 24){
		if(bmp_hdr -> bits_per_pixel != 16){
			return false;
		}
	}
	fseek(fp,0,SEEK_END);
	int fsz = ftell(fp);
	if(bmp_hdr -> size != fsz){
		return false;
	}
	uint32_t imsz = fsz - BMP_HEADER_SIZE;
	if(bmp_hdr -> image_size_bytes != imsz){
		return false;
	}
	fseek(fp,0,SEEK_SET);
	return true;
}

bool _isvalid(FILE *fp){
	BMPImage *chkImg = malloc(sizeof(*chkImg));
	if(fread(&(chkImg -> header.type),sizeof(chkImg -> header.type),1,fp) != 1){
		free(chkImg);
		return false;	
	}
	else if(fread(&(chkImg -> header.size),sizeof(chkImg -> header.size),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.reserved1),sizeof(chkImg -> header.reserved1),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.reserved2),sizeof(chkImg -> header.reserved2),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.offset),sizeof(chkImg -> header.offset),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.dib_header_size),sizeof(chkImg -> header.dib_header_size),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.width_px),sizeof(chkImg -> header.width_px),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.height_px),sizeof(chkImg -> header.height_px),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.num_planes),sizeof(chkImg -> header.num_planes),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.bits_per_pixel),sizeof(chkImg -> header.bits_per_pixel),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.compression),sizeof(chkImg -> header.compression),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.image_size_bytes),sizeof(chkImg -> header.image_size_bytes),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.x_resolution_ppm),sizeof(chkImg -> header.x_resolution_ppm),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.y_resolution_ppm),sizeof(chkImg -> header.y_resolution_ppm),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.num_colors),sizeof(chkImg -> header.num_colors),1,fp) != 1){
		free(chkImg);
		return false;
	}
	else if(fread(&(chkImg -> header.important_colors),sizeof(chkImg -> header.important_colors),1,fp) != 1){
		free(chkImg);
		return false;
	}
	fseek(fp,0,SEEK_SET);
	free(chkImg);
	return true;
}

BMPImage *read_bmp(FILE *fp, char **error){
	if(fp == NULL){
		strcpy(*error,"File not found");
		return NULL;
	}
	
	if(_isvalid(fp) != true){
		strcpy(*error,"Invalid File");
		return NULL;
	}

	BMPHeader tHeader;
	int readSuccess = fread(&tHeader,sizeof(tHeader),1,fp);
	if(readSuccess == 0){
		strcpy(*error,"Cannot read the header");
		return NULL;
	}
	bool header_check = check_bmp_header(&tHeader, fp);
	BMPImage *image = malloc(sizeof(*image));
	if(image == NULL){
		strcpy(*error,"Cannot assign heap memory to the bmp image");
		free_bmp(image);
		return NULL;
	}
	if(header_check){
		image -> header = tHeader;
		unsigned char *imDat = malloc(tHeader.image_size_bytes);
		if(imDat == NULL){
			strcpy(*error,"Failed to read data");
			return NULL;
		}
		fseek(fp,tHeader.offset,SEEK_SET);
		fread(imDat,tHeader.image_size_bytes,1,fp);
		image -> data = imDat;
		return image;
	}
	else{
		strcpy(*error,"Cannot read image");
		free_bmp(image);
		return NULL;
	}
	fseek(fp,0,SEEK_SET);
	free_bmp(image);
	return NULL;
}

bool write_bmp(FILE *fp, BMPImage *image, char **error){
	if(fp == NULL){
		*error = "Cannot find the open file";
		return false;
	}
	
	if(image == NULL){
		strcpy(*error,"Blank Image data");
		return false;
	}
	
	bool successFlag = false;
	fseek(fp, 0, SEEK_SET);
	int writeHeaderSuc = fwrite(&image -> header,sizeof(image -> header),1,fp);
	if(writeHeaderSuc == 0){
		strcpy(*error,"Error writing the header");
		return false;
	}
	int writeSuccess = fwrite(image->data,image -> header.image_size_bytes,1,fp);
	if(writeSuccess != 0){
		successFlag = true;
	}
	else{
		strcpy(*error,"Error writing the image data to file");
		return false;
	}
	return successFlag;
}

BMPImage *crop_bmp(BMPImage *image, int x, int y, int w, int h, char **error){
	if(image == NULL){
		strcpy(*error,"Image file not proper");
		return NULL;
	}
	
	BMPImage *cropImage = malloc(sizeof(*cropImage));	
	cropImage -> header = image -> header;
	cropImage -> header.width_px = w;
	cropImage -> header.height_px = h;
	int k = x;
	printf("\n");
	while(k < (x+ 3*w)){
		printf("%x",image -> data[k]);
		k++;
	}
	cropImage -> data = malloc(sizeof(*cropImage -> data) * image -> header.image_size_bytes);
	memcpy(cropImage -> data,image -> data,sizeof(*cropImage -> data) * (image -> header.image_size_bytes));
	return cropImage;
}

void free_bmp(BMPImage *image){
	if(image != NULL)
	{
		free(image -> data);
		free(image);
	}
}
