package midware

import (
	"errors"
	"fmt"
	"net/http"
	"time"

	// "testLogin/controller"

	"github.com/gin-gonic/gin"
	"github.com/golang-jwt/jwt/v4"
)
func GetKey(_ *jwt.Token)(interface{} , error){
	return mySecret , nil
}
type MyClaims struct{
	UserID int64 `json:"user_id"`
	jwt.RegisteredClaims
}
//生成token
var mySecret = []byte("haomiao000")
func GenToken(userID int64) (string , error){
	claims := MyClaims{
		UserID : userID,
		RegisteredClaims: jwt.RegisteredClaims{
			ExpiresAt: jwt.NewNumericDate(time.Now().Add(1*time.Hour)),
			Issuer: "jwt",
		},
	}
	token := jwt.NewWithClaims(jwt.SigningMethodHS256 , claims)
	return token.SignedString(mySecret)
}
//解析token
func ParseToken(tokenString string) (*MyClaims , error){
	var claims MyClaims
	token , err := jwt.ParseWithClaims(tokenString , &claims ,  GetKey)
	if err != nil{
		return nil , fmt.Errorf("parsing token: %w" , err)
	}
	
	if !token.Valid {
		return nil , errors.New("invalid token")
	}
	return &claims , nil
}

func AuthMiddleware() gin.HandlerFunc{
	return func(c *gin.Context){
		// fmt.Println("here is wrong -")
		tokenString := c.GetHeader("Authorization")
		if tokenString == ""{
			c.JSON(http.StatusUnauthorized, gin.H{"error": "Unauthorized"})
			c.Abort()
			return
		}
		// fmt.Println("here is wrong --")
		claims , err := ParseToken(tokenString)
		if err != nil{
			c.JSON(http.StatusUnauthorized, gin.H{"error": "Unauthorized"})
			c.Abort()
			return
		}
		fmt.Println("here is wrong ---")
		c.Set("UID" , claims.UserID)
		c.Next()
	}
}
func GetUserHandler(c *gin.Context) {
	userID, exists := c.Get("UID")
	if !exists {
		c.JSON(http.StatusInternalServerError, gin.H{"error": "Internal Server Errorr"})
		return
	}
	fmt.Println(userID)

	c.JSON(http.StatusOK, gin.H{"UID": userID})
}