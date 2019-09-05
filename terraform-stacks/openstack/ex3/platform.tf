/* variable declarations */

variable image_id {
  default = "ac9d6735-7c2b-4ff1-90e9-b45225fd80a9"
}

variable flavor_id {
  default = "2"
}

variable region {
  default = "lab2"
}

variable public {
	default = "ee231665-a5b5-4ec3-92d2-ce62b7491ccb"
}

variable key_pair {
  default = "mykey"
}

variable instances {
   type = "map"   
   
   default   {     
   backend = "2"   
   } 
 }
