var matrix_one = [[1,2,3,4],[1,1,2,0],[3,3,1,2]];//2x3 
/*
1 2 3  1 2 2x2
1 2 3  1 2
       1 2*/
var matrix_two = [[2,5],[7,10],[1,1],[3,4]];
var result = matrix_multiplication(matrix_one,matrix_two);
print_matrix(result);
function validate_matrices(mat1,mat2){
    mat1_rows = mat1.length;
    mat2_rows = mat2.length;
    mat1_cols =mat1[0].length;
    mat2_cols =mat2[0].length;
    for(var i = 0 ; i < mat1_rows;i++){
        if(mat1_cols != mat1[i].length){
            return 0;
        }
    }
    for(var i = 0 ; i < mat2_rows;i++){
        if(mat2_cols != mat2[i].length){
            return 0;
        }
    }
    if(mat1_cols != mat2_rows){
        return 0;
    }
    return 1;

}
function create_matrix(matrix1,matrix2){
    var new_arr = [];
    mat1_rows = matrix1.length;
    mat1_cols = matrix1[0].length;
    mat2_rows = matrix2.length;
    mat2_cols = matrix2[0].length;
    //red na purvo
    //koloni na vtoro
    for(var i = 0 ;i < mat1_rows;i++){
        new_arr.push([]);
    }
    return new_arr;
}
function matrix_multiplication(mat1,mat2){
    var result = validate_matrices(mat1,mat2);
    if(!result){
        return 0;
    }
    new_matrix = create_matrix(mat1,mat2);
    var mat2_cols = mat2[0].length;
    for(var i = 0 ; i < mat1.length;i++){
        for(var k = 0;k<mat2_cols;k++){
            var curr_res = 0;
            for(var j = 0 ; j < mat1[i].length;j++){
                curr_res += mat1[i][j]*mat2[j][k];
                
            }
            new_matrix[i].push(curr_res); // fix logic
        }
    }
    return new_matrix;
}
function print_matrix(mat){
    for(var i = 0 ; i < mat.length;i++){
        for(var j = 0 ; j < mat[i].length;j++){
            console.log("%d ",mat[i][j]);
        }
        console.log("");
    }
}
for(var i = 0 ; i < matrix_one.length;i++){
    console.log(matrix_one[i].length);
}