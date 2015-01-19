#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/joystick.h>
#include <linux/input.h>
#include <fcntl.h>
#include <X11/Xlib.h>

int main()
{
//***********************************Finding Out the Device Handler File************************************************//
	FILE *device=fopen("/proc/bus/input/devices","r");    
	char a[100],event[20],event1[10];
	char c;
	int l=0,i=1;
	while(fscanf(device,"%c",&c)==1&&!feof(device))
	{
		if(c!='\n')
			a[l++]=c;
		else
		{
			a[l++]='\0';
			if(a[0]=='N')
			{
				printf("%d.",i++);
				puts(a);
			}
			l=0;
		}
	}
	int s,j;
	if(i>1)
		while(1)
		{

			printf("\nSelect Your Device Number  :  ");
			scanf("%d",&s);
			if(s<0||s>i-1)
				printf("\nSorry not a valid selection");
			else
				break;
		}
	else
	{
		printf("\nNo devices Found exiting...");
		exit(0);
	}
	fseek(device,0,SEEK_SET);
	i=1;
	while(fscanf(device,"%c",&c)==1&&!feof(device))
	{
		if(c!='\n')
			a[l++]=c;
		else
		{
			a[l++]='\0';
			l=0;

			if(a[0]=='H'&&i++==s)
			{
				j=0;
				l=12;
				while(l<strlen(a))
				{
					event[j++]=a[l++];
				}
				event[j]='\0';

				j=0;
				while(j<strlen(event))
				{
					if(event[j]==' ')
					{
						i=0;
						while(j<strlen(event)-2)
							event1[i++]=event[++j];
						event1[i]='\0';

						break;
					}
					j++;
				}
				break;
			}
		}
	}
//***************************Handler name extraction finished************************************************************//
	
  	struct js_event ie;
  	Display *disp;
  	Window root, child;
  	int initX, initY, winX, winY,s1,flag=0,fd;
  	unsigned int mask;

  	disp = XOpenDisplay(NULL);
  	XQueryPointer(disp,DefaultRootWindow(disp),&root,&child,&initX,&initY,&winX,&winY,&mask); //Getting initial position coordinates 
 	XWindowAttributes attrib;  
	XGetWindowAttributes(disp, root,&attrib);   //Getting the window max attributes
	fflush(stdout);
	char temp[1];
	printf("\n\nThe Screen Resolution is %dx%d\nMax X Coordinate  : %d  Max Y Coordinate  : %d\n",attrib.width,attrib.height,attrib.width-1,attrib.height-1);
	printf("\n\nPress ENTER to start monitoring the co-ordinates...");
	gets(temp);
	printf("\n");
	char M[10]="";
	strcat(M,"/dev/input/");
	strcat(M,event1);


  	if((fd = open("/dev/input/js0", O_RDONLY)) == -1)     //Getting file descriptor for /dev/input/eventX
 	{
    
  	 	 perror("Restart with administrative Privileges ,Error");
 		   exit(0);
	}
	int curx=initX,cury=initY;

  	

	unsigned char ch,dh;	
  	while(read(fd, &ie, sizeof(ie)))
	{
		printf("new event\n");
		
		printf("type=%d number=%d value=%d\n",ie.type,ie.number,ie.value);
		
	}
	
 	return 0;
}
