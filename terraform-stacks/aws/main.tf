resource "aws_instance" "webserver" {
  ami           = "ami-0c55b159cbfafe1f0"
  instance_type = "t2.micro"
  key_name = "aws1"
  user_data = "${file("install_apache2.sh")}"
  tags {
    Name = "test-instance3"
  }
}




