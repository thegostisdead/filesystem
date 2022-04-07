# FileSystem implementation

The goal of this lab is to implement a file system. We need to implement basics operations. 

## Structure

![Structure](schema.png)

## Types 

### Inode : 

>  — size of filename, 1 byte.   
>  — filename, 8 bytes   
>  — size of file in bytes, 1 byte  
>  — 6 data blocks index, 1 byte each 

### Bitmap :

>  Byte array 


## How to read : 

<ol>
  <li>Read file system file (read mode)</li>
  <li>Read number of blocks</li>
  <li>Read number of inodes </li>
  <li>Read blocks bitmap </li>
  <li>Read inodes bitmap  </li>
  <li>Read blocks  </li>
  <li>Read inodes   </li>
  <li>Close file    </li>
</ol>

## How to write :

TODO
