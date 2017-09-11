#include "uip.h"
#include "httpd.h"
#include <httpd.h>
#include "fs.h"
#include "fsdata.h"
#include <asm/addrspace.h>

#include "../../include/image.h"

#define HTTP_NONE		0
#define HTTP_FILE		1
#define HTTP_POST_HEAD		2
#define HTTP_POST_BODY		3
#define HTTP_BOUN		4
#define HTTP_FW_NAME		5
#define HTTP_FIRMWARE		6

static unsigned char flag;
static unsigned char *ptr_to_ram; //указатель на память куда пишем пришедьшие данные
extern ulong load_addr; //указатель на начало памяти куда можно писать

#define PRINT(x) printf("%s", x)
#define PRINTLN(x) printf("%s\n", x)

struct httpd_state *hs;

extern const struct fsdata_file file_index_html;
extern const struct fsdata_file file_404_html;
extern const struct fsdata_file file_flash_html;
extern const struct fsdata_file file_error_html;

extern int httpd_upload_complete;
extern unsigned char *httpd_upload_data;
unsigned char *upload_data;
extern ulong		NetBootFileXferSize;
int upload_running = 0;

#define ISO_G        0x47
#define ISO_E        0x45
#define ISO_T        0x54
#define ISO_P        0x50
#define ISO_O        0x4f
#define ISO_S        0x53
#define ISO_T        0x54
#define ISO_slash    0x2f
#define ISO_c        0x63
#define ISO_g        0x67
#define ISO_i        0x69
#define ISO_space    0x20
#define ISO_nl       0x0a
#define ISO_cr       0x0d
#define ISO_a        0x61
#define ISO_t        0x74
#define ISO_hash     0x23
#define ISO_period   0x2e

static char eol[3] = { 0x0d, 0x0a, 0x00 };
static char eol2[5] = { 0x0d, 0x0a, 0x0d, 0x0a, 0x00 };

static int boundary_len = 0;


/* we use this so that we can do without the ctype library */
#define is_digit(c)	((c) >= '0' && (c) <= '9')
static int atoi(const char *s)
{
	int i=0;

	while (is_digit(*s))
		i = i*10 + *(s++) - '0';
	return i;
}

void
httpd_init(void)
{
	fs_init();
	uip_listen(HTONS(80));
}

void
httpd_appcall(void)
{
	struct fs_file fsfile;
	switch(uip_conn->lport) {
	case HTONS(80):
		hs = (struct httpd_state *)(uip_conn->appstate);
		if(uip_connected())
		{
			hs->state = HTTP_NONE;
			hs->count = 0;
			return;
		} else if(uip_poll())
		{
			if(hs->count++ >= 1000) {
				uip_abort();
			}
			return;
		} else if(uip_newdata() && hs->state == HTTP_NONE)
		{
			if(uip_appdata[0] == ISO_G &&
				uip_appdata[1] == ISO_E &&
				uip_appdata[2] == ISO_T &&
				uip_appdata[3] == ISO_space)
			{
				hs->state = HTTP_FILE;
			}
			if(uip_appdata[0] == ISO_P &&
				uip_appdata[1] == ISO_O &&
				uip_appdata[2] == ISO_S &&
				uip_appdata[3] == ISO_T &&
				uip_appdata[4] == ISO_space)
			{
				hs->state = HTTP_POST_HEAD;
				hs->upload_total=0;
				hs->upload=0;
				ptr_to_ram=(uchar*)load_addr;
			}
			if(hs->state == HTTP_NONE)
			{
				uip_abort();
				return;
			}
			if(hs->state == HTTP_FILE)
			{
				int i;
				for(i = 4; i < 40; ++i)
				{
					if(uip_appdata[i] == ISO_space ||
						uip_appdata[i] == ISO_cr ||
						uip_appdata[i] == ISO_nl)
					{
						uip_appdata[i] = 0;
						break;
					}
				}

				PRINT("request for file ");
				PRINTLN(&uip_appdata[4]);
				if(uip_appdata[4] == ISO_slash &&
					uip_appdata[5] == 0)
				{
					fs_open(file_index_html.name, &fsfile);
				} else {
					if(!fs_open((const char *)&uip_appdata[4], &fsfile))
					{
						PRINTLN("couldn't open file");
						fs_open(file_404_html.name, &fsfile);
					}
				}
				hs->script = 0;
				hs->state = HTTP_FILE;
				hs->dataptr = fsfile.data;
				hs->count = fsfile.len;
			}
		}

		if(hs->state == HTTP_POST_HEAD)
		{
			if (uip_newdata())
			{
				unsigned char *temp_ptr=(unsigned char *)load_addr;

				memcpy(ptr_to_ram,(void*)uip_appdata,uip_datalen());
				hs->upload+=uip_datalen();
				ptr_to_ram=&ptr_to_ram[uip_datalen()];
				ptr_to_ram[0]='\0';
				ulong i;
				flag=1;
				i=0;
				while (flag)
				{
					if (i>=((hs->upload)-3)) flag=0;

					if ((temp_ptr[i]==0x0d)&&(temp_ptr[i+1]==0x0a)&&(temp_ptr[i+2]==0x0d)&&(temp_ptr[i+3]==0x0a))
					{
						/*int t;
						for (t=0;t<hs->upload;t++) putc(temp_ptr[t]);
						printf("header- %d bytes\n",hs->upload);*/

						char* clen=strstr(temp_ptr,"Content-Length:");
						unsigned char *next;
                       				if(clen)
                        			{
                                			clen += sizeof("Content-Length:");
                                			next = (unsigned char *)strstr(clen, eol);
                                			if(next)
                                			{
                                        			hs->upload_total = atoi(clen);
                                        			printf("expecting %d bytes\n", hs->upload_total);
                                			} else {
                                        			uip_close();
                                        			return;
                                			}
                                                	hs->state=HTTP_POST_BODY;
                                                        ptr_to_ram=(unsigned char *)load_addr;
							flag=0;
							uip_appdata=&uip_appdata[uip_len-((hs->upload)-i-4)];
							//printf("%d %d %d\n",uip_len,hs->upload,i);
							uip_len=(hs->upload)-i-4;
							//printf("%d   %x %x %x\n",uip_len,uip_appdata[0],uip_appdata[1],uip_appdata[2]);
							hs->upload=0;
                        			} else {
							uip_close();
							return;
						}
					}
					i++;
				}
			}
		}

		if(hs->state == HTTP_POST_BODY)
		{
			if ((uip_newdata())&&(uip_len>0))
			{
                                memcpy(ptr_to_ram,(void*)uip_appdata,uip_datalen());
                                hs->upload+=uip_datalen();
				ptr_to_ram=&ptr_to_ram[uip_datalen()];
				ptr_to_ram[0]='\0';
				unsigned char *temp_ptr=(unsigned char *)load_addr;
				ulong i;
				flag=1;
				i=0;
				while (flag)
                                {
					if (i>=((hs->upload)-3)) flag=0;
                                        if ((temp_ptr[i]==0x0d)&&(temp_ptr[i+1]==0x0a)&&(temp_ptr[i+2]==0x0d)&&(temp_ptr[i+3]==0x0a))
                                        {
						/*int u;
						for (u=0;u<i+4;u++) putc(temp_ptr[u]);*/
                        			char *boundary_start = strstr(temp_ptr, "---");
                        			if(!boundary_start)
                        			{
                                			printf("not found boundary start\n");
                                			uip_close();
                                			return;
                        			}
                        			char *end = strstr(boundary_start, eol);
                        			if(!end)
                        			{
                                			printf("not found boundary end");
                                			uip_close();
                                			return;
                        			}
                        			boundary_len = (unsigned long)end - (unsigned long)boundary_start;
						//printf("boundary length - %d\n",boundary_len);
						
                        			end = (unsigned char *)strstr((char *)boundary_start, "name=\"firmware\";");
                        			if(!end)
                        			{
                                			printf("not found firmware file name ");
                                			uip_close();
                                			return;
                       				 }
						hs->state=HTTP_FIRMWARE;
                                                ptr_to_ram=(unsigned char *)load_addr;
                                                flag=0;
                                                uip_appdata=&uip_appdata[uip_len-((hs->upload)-i-4)];
                                                uip_len=(hs->upload)-i-4;
						hs->upload_total-=((hs->upload)-uip_len);
						//printf("%d %d %d\n",hs->upload_total,hs->upload,uip_len);
						hs->upload=0;
						//printf("%d   %x %x %x\n",uip_len,uip_appdata[0],uip_appdata[1],uip_appdata[2]);
					}
					i++;
				}
			}
		}

		if(hs->state == HTTP_FIRMWARE)
		{
                        if ((uip_newdata())&&(uip_len>0))
                        {
                                memcpy(ptr_to_ram,(void*)uip_appdata,uip_datalen());
                                hs->upload+=uip_datalen();
				ptr_to_ram=&ptr_to_ram[uip_datalen()];
				if (hs-> upload >= hs->upload_total)
				{	
					hs->upload_total=(hs->upload_total)-boundary_len-4-2;
					//проверка образа
					int broken = 0;
					broken = firmware_check((unsigned char *)load_addr);
#if 0
					unsigned long len = 0, chksum = 0;
					image_header_t hdr1 ;
					unsigned char *hdr1_addr;
	
					hdr1_addr = (unsigned char *)load_addr;
	
					memmove(&hdr1, (char *)hdr1_addr, sizeof(image_header_t));

					printf("\n=================================================\n");
					printf("\nCheck image validation:\n");

					/* Check header magic number */
					printf ("Image Header Magic Number --> ");
					if (ntohl(hdr1.ih_magic) != IH_MAGIC) {
						broken = 1;
						printf("Failed!ImageHeaed=0x%x.\n",ntohl(hdr1.ih_magic));
					}
					else
						printf("OK\n");

					/* Check header crc */
					/* Skip crc checking if there is no valid header, or it may hang on due to broken header length */
					if (broken == 0) {
						printf("Image Header Checksum --> ");
						len  = sizeof(image_header_t);
						chksum = ntohl(hdr1.ih_hcrc);
						hdr1.ih_hcrc = 0;
						if (crc32(0, (char *)&hdr1, len) != chksum) {
							broken = 1;
							printf("Failed\n");
						}
						else
							printf("OK\n");
					}

					/* Check data crc */
					/* Skip crc checking if there is no valid header, or it may hang on due to broken data length */
					if (broken == 0) {
						printf("Image Data Checksum --> ");
						len = ntohl(hdr1.ih_size);
						chksum = ntohl(hdr1.ih_dcrc);
						if (crc32(0, (char *)(hdr1_addr + sizeof(image_header_t)), len) != chksum)
						{
							broken = 1;
							printf("Failed\n");
						}
						else
							printf("OK\n");
					}
					printf("\n=================================================\n");
#endif
					if (broken)
					{
						fs_open(file_error_html.name, &fsfile);
						hs->script = 0;
						hs->state = HTTP_FILE;
						hs->dataptr = fsfile.data;
						hs->count = fsfile.len;
					} else {
						upload_running = 1;
						NetBootFileXferSize = hs->upload_total;
						fs_open(file_flash_html.name, &fsfile);
						//printf("file_error_html=0x%x\n",(unsigned long *) &file_error_html);
						//printf("file_flash_html.name=%x\n",(unsigned long *) &file_flash_html.name);
						//printf("load_addr=0x%x\n",(unsigned long *)load_addr);
						hs->script = 0;
						hs->state = HTTP_FILE;
						hs->dataptr = fsfile.data;
						hs->count = fsfile.len;
					}
				}
			}
		}
		uip_len=0;

		if(hs->state == HTTP_FILE)
		{
			if(uip_acked())
			{
				if(hs->count >= uip_conn->len)
				{
					hs->count -= uip_conn->len;
					hs->dataptr += uip_conn->len;
				} else {
					hs->count = 0;
				}
				if(hs->count == 0)
				{
					if(upload_running)
					{
					//	printf("upload complited...\n");
						httpd_upload_complete = 1;
					//	for(i = 0; i < hs->upload_total; i++)
					//		printf("%c", httpd_upload_data[i]);
					}
					uip_close();
				}
			}
			uip_send((unsigned char *)hs->dataptr, hs->count);
		}
		break;

	default:
		uip_abort();
		break;
	}
}


int 
do_http_upgrade(const unsigned char *data, const ulong size)
{
}

int
do_http_progress(const int state) 
{
	static unsigned long int i;
	static int led_sate=1;
//	printf("\nheqiang---\n");
switch(state)
{
case HTTP_PROGRESS_TIMEOUT:
#if 0
	if (i==1000)
	{
	puts("T");
	i=0;
	}
	else
	i++;
	udelay (1000);
#endif
		if(get_timer(i) > (CFG_HZ/10))
		{
			//printf("\n addr = 0x%08X ,cnt=%d ",addr,left);
			//printf("T "); //lintel
//			printf("\n--------------------wait-------\n");
			if(led_sate) led_control(led_sate);
			else led_control(led_sate);
			i = get_timer(0);
			led_sate=!led_sate;
		}

	break;
}

}

