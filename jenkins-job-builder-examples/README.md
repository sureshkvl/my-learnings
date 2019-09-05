# jenkins-job-builder-examples

Followed this tutorial

https://dzone.com/articles/jenkins-job-builder-tutorial-ccjpe-11

Installation

sudo pip install jenkins-job-builder



Examples jobs



History:

 1905  sudo pip install jenkins-job-builder
 1908  cat jenkins_jobs.ini 
 1920  sudo jenkins-jobs --conf jenkins_jobs.ini update example1.yaml 
 1923  sudo jenkins-jobs --conf jenkins_jobs.ini update default.yaml 
 1925  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old jobs
 1927  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old example1
 1929  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old example1.yaml
 1931  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old test_job
 1932  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old jobs
 1933  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old example1.yaml 
 1934  sudo jenkins-jobs --conf jenkins_jobs.ini update --delete-old example1
 1936  sudo jenkins-jobs --conf jenkins_jobs.ini update 
 1937  sudo jenkins-jobs --conf jenkins_jobs.ini update conf
 1938  sudo jenkins-jobs --conf jenkins_jobs.ini update 
 1939  sudo jenkins-jobs --conf jenkins_jobs.ini update project3.yaml 
 1940  sudo jenkins-jobs --conf jenkins_jobs.ini update project3.yaml  template1.yaml 
 1941  sudo jenkins-jobs --conf jenkins_jobs.ini update project3.yaml  .
 1942  sudo jenkins-jobs --conf jenkins_jobs.ini update .
 1943  sudo jenkins-jobs --conf jenkins_jobs.ini update project3.yaml 
 1944  sudo jenkins-jobs --conf jenkins_jobs.ini update 
 1945  sudo jenkins-jobs --conf jenkins_jobs.ini update . job3
 1946  sudo jenkins-jobs --conf jenkins_jobs.ini update . job3*
 1947  sudo jenkins-jobs --conf jenkins_jobs.ini update . job3
 1948  sudo jenkins-jobs --conf jenkins_jobs.ini update . 
 1949  sudo jenkins-jobs --conf jenkins_jobs.ini update job4
 1950  sudo jenkins-jobs --conf jenkins_jobs.ini update project4.yaml 
 1951  sudo jenkins-jobs --conf jenkins_jobs.ini update project4.yaml  .
 1952  sudo jenkins-jobs --conf jenkins_jobs.ini update job4*
 1953  sudo jenkins-jobs --conf jenkins_jobs.ini update job4
 1954  sudo jenkins-jobs --conf jenkins_jobs.ini update job2
 1955  sudo jenkins-jobs --conf jenkins_jobs.ini update . job2
 1956  sudo jenkins-jobs --conf jenkins_jobs.ini update . job3
 1957  sudo jenkins-jobs --conf jenkins_jobs.ini update . job4
 1958  sudo jenkins-jobs --conf jenkins_jobs.ini update . job5
 1959  sudo jenkins-jobs --conf jenkins_jobs.ini update .
 1960  sudo jenkins-jobs --conf jenkins_jobs.ini job3
 1961  sudo jenkins-jobs --conf jenkins_jobs.ini . job3
 1962  sudo jenkins-jobs --conf jenkins_jobs.ini update . job2
 1963  sudo jenkins-jobs --conf jenkins_jobs.ini update / job2
 1964  sudo jenkins-jobs --conf jenkins_jobs.ini update . job2
 1965  sudo jenkins-jobs --conf jenkins_jobs.ini update ../jenkins-job-builder-examples/ job2
 1967  sudo jenkins-jobs --conf jenkins_jobs.ini update ../jenkins-job-builder-examples/ job3
 1968  sudo jenkins-jobs --conf jenkins_jobs.ini update ../jenkins-job-builder-examples/ test_job
 1969  sudo jenkins-jobs --conf jenkins_jobs.ini update . test_job
 1970  sudo jenkins-jobs --conf jenkins_jobs.ini delete test_job
 1971  sudo jenkins-jobs --conf jenkins_jobs.ini delete job1_job
 1972  sudo jenkins-jobs --conf jenkins_jobs.ini delete job*
 1973  sudo jenkins-jobs --conf jenkins_jobs.ini delete_all
 1974  sudo jenkins-jobs --conf jenkins_jobs.ini delete-all
