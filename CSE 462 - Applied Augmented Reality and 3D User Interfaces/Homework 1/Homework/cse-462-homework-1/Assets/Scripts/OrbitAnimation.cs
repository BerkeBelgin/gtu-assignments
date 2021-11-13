using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OrbitAnimation : MonoBehaviour
{
    public Transform center;
    public float preiod = 1.0F;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.RotateAround(center.position, Vector3.up, preiod * Time.deltaTime * 360);
    }
}
