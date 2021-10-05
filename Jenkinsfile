pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh "set echo off"
                sh "echo Building..."
                sh "g++ src/addition.cpp -o bin/build/add.out"
                sh "g++ src/multiplication.cpp -o bin/build/mul.out"
                sh "g++ src/subtraction.cpp -o bin/build/sub.out"
                script {
                    stash includes: "bin/build/*", name: "builds"
                }
            }
        }
        stage('Test') {
            steps {

                sh "set echo off"
                sh "echo Running tests"
                sh "g++ tests/client_tester.cpp - o bin/tests/tester.out"
                sh "echo Testing addition microservice"
                sh "bin/build/add.out 33983 &"
                sh "bin/tests/tester.out 33983 10 5"
                sh "echo Testing multiplication microservice"
                sh "bin/build/mul.out 33983 &"
                sh "bin/tests/tester.out 33983 10 5"
                sh "echo Testing subtraction microservice"
                sh "bin/build/sub.out 33983 &"
                sh "bin/tests/tester.out 33983 10 5"
            }
        }
        stage('Publish') {
            steps {
                sh "set echo off"
                sh "zip -r build_Debian bin/build/*"
                archiveArtifacts artifacts: "build_Debian.zip", fingerprint: true
                script {
                    unstash "builds"
                }
            }
        }
    }
}